#include "renderwidget.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

RenderWidget::RenderWidget(QWidget *parent)
{
    qDebug()  << "---Render Window Contractor---";
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

RenderWidget::~RenderWidget()
{
    makeCurrent();
    delete m_computeShader;
    delete m_vertexShader;
    delete m_fragmentShader;
    delete m_tex_output;
    delete m_tex_input;
    delete m_hdri;
    delete m_renderProgram;
    delete m_computeProgram;
    delete m_indexBuffer;
    delete m_vertexBuffer;
}


void RenderWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

    qDebug() << "version: "
                 << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GLSL version: "
                 << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    // VAO
    m_vao.create();
    m_vao.bind();

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };
    static const GLushort g_element_buffer_data[] = { 0, 1, 2, 3 };

    // VBO
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(g_vertex_buffer_data,sizeof(g_vertex_buffer_data));

    // IBO
    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer->bind();
    m_indexBuffer->allocate(g_element_buffer_data,sizeof(g_element_buffer_data));


    // Texture Output(1)
    glActiveTexture(GL_TEXTURE1);
    m_tex_output = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_tex_output->create();
    m_tex_output->setFormat(QOpenGLTexture::RGBA32F);
    m_tex_output->setSize(tex_w,tex_h);
    m_tex_output->setMinificationFilter(QOpenGLTexture::Linear);
    m_tex_output->setMagnificationFilter(QOpenGLTexture::Linear);
    m_tex_output->allocateStorage();
    m_tex_output->bind();
    glBindImageTexture(1, m_tex_output->textureId(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    // Texture Input(0)
    glActiveTexture(GL_TEXTURE0);
    m_tex_input = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_tex_input->create();
    m_tex_input->setFormat(QOpenGLTexture::RGBA32F);
    m_tex_input->setSize(tex_w,tex_h);
    m_tex_input->setMinificationFilter(QOpenGLTexture::Linear);
    m_tex_input->setMagnificationFilter(QOpenGLTexture::Linear);
    m_tex_input->allocateStorage();
    m_tex_input->bind();
    glBindImageTexture(0, m_tex_input->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

    // Shader
    m_computeShader = new QOpenGLShader(QOpenGLShader::Compute);
    m_computeShader->compileSourceFile(":/render_cshader.glsl");
    m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_vertexShader->compileSourceFile(":/render_vshader.glsl");
    m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_fragmentShader->compileSourceFile(":/render_fshader.glsl");

    m_computeProgram = new QOpenGLShaderProgram();
    m_computeProgram->addShader(m_computeShader);
    m_computeProgram->link();
    m_computeProgram->bind();
    m_renderProgram = new QOpenGLShaderProgram();
    m_renderProgram->addShader(m_vertexShader);
    m_renderProgram->addShader(m_fragmentShader);
    m_renderProgram->link();
    m_renderProgram->bind();


    // HDRI (3)
    // STB IMAGE
    int width, height, bpp;
    float* data = stbi_loadf("E:/Pictures/Textures/_HDRI/arboretum/arboretum_4k.hdr", &width, &height, &bpp, 4);

    GLuint hdri;
    glGenTextures(1, &hdri);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, hdri);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, data);
    glBindImageTexture(3, hdri, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);

    // Send Pos
    GLint posPtr = glGetAttribLocation(m_renderProgram->programId(), "pos");
    glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posPtr);


    // Accum (0)
    // TODO: メンバ変数を消去
    glGenBuffers(1, &accum);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, accum);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned), &accumN, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, accum);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // Theta (1)
    float theta = qDegreesToRadians(yRot);
    qDebug() << "Theta:" << theta;
    GLuint theta_id;
    glGenBuffers(1, &theta_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, theta_id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float), &theta, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, theta_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 1);

    // Phi (2)
    float phi = qDegreesToRadians(xRot);
    qDebug() << "Phi:" << phi;
    GLuint phi_id;
    glGenBuffers(1, &phi_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, phi_id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float), &phi, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, phi_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 2);

    // Seed (2)
    std::vector<QVector4D> seedDataBuffer;
    for (int i = 0; i < tex_w; i++) {
        for (int j = 0; j < tex_h; j++) {
            seedDataBuffer.push_back(QVector4D(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX),
                                               float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX)));
        }
    }
    GLuint seed;
    glGenTextures(1, &seed);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, seed);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tex_w, tex_h, 0, GL_RGBA, GL_FLOAT, &seedDataBuffer[0]);
    glBindImageTexture(2, seed, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI);

    m_vao.release();
}



void RenderWidget::paintGL(){
    // compute
    m_computeProgram->bind();
    glDispatchCompute(tex_w, tex_h ,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // draw
    m_renderProgram->bind();
    m_vao.bind();
    glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_SHORT,0);


    m_vao.release();

    if(frame > 1000){
        rendering = false;
    }

    qDebug() << "Rendering:" <<  ++frame;

    if(rendering){
        update();
    }
}

void RenderWidget::resizeGL(int w, int h){
    //glViewport(0, 0, w, h);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(0, 1, 0, 1, 0, 1);
    //glMatrixMode(GL_MODELVIEW);
}

// Slots
void RenderWidget::stopRendering()
{
    rendering = false;
}