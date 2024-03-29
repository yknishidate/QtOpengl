#define STB_IMAGE_IMPLEMENTATION
#include "renderwidget.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>

RenderWidget::RenderWidget(QWidget *parent){
    qDebug()  << "---Render Widget Contractor---";

    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

RenderWidget::~RenderWidget(){
    makeCurrent();
    delete m_computeShader;
    delete m_vertexShader;
    delete m_fragmentShader;
    delete m_renderProgram;
    delete m_computeProgram;
    delete m_indexBuffer;
    delete m_vertexBuffer;
}



void RenderWidget::initializeGL(){
    qDebug()  << "---Initialize GL---";
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

    // Check Data
    for(int i = 0; i < models.size(); i++){
        qDebug() << "Model Name  : " << QString::fromStdString( models[i]->getName() );
    }
    qDebug() << "version     : " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GLSL version: " << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));


    // VAO
    m_vao.create();
    m_vao.bind();

    static const GLfloat g_vertex_buffer_data[] = { -1.0f, -1.0f,    -1.0f,  1.0f,    1.0f, -1.0f,    1.0f,  1.0f };
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

    // Texture Input(0)
    QOpenGLTexture *m_tex_input;
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

    // Texture Output(1)
    QOpenGLTexture *m_tex_output;
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
    accumN = 1;
    glGenBuffers(1, &accum);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, accum);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned), &accumN, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, accum);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

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
    glBindImageTexture(2, seed, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);


    //--------------------------------------------------
    //                 Model Data
    //--------------------------------------------------
    // Model Data
    std::vector<float> radData;
    std::vector<QVector4D> posData;
    std::vector<QVector4D> planePosData;
    std::vector<int> meterialTypeData;
    std::vector<QVector4D> materialDiffColorData;
    std::vector<QVector4D> materialSpecColorData;
    std::vector<QVector4D> materialTransColorData;
    std::vector<QVector4D> materialLightColorData;
    std::vector<float> materialIorData;

    // Load Models
    for(int i =0; i < models.size(); i++){
        // Load Sphere or Plane
        if(models[i]->getType() == ModelType::SPHERE){
            radData.push_back(models[i]->getRadius());
            posData.push_back(QVector4D(models[i]->getPosition(), 1));
        }else if(models[i]->getType() == ModelType::PLANE){
            radData.push_back(10000);
            posData.push_back(QVector4D((QVector3D(0, -10000, 0) + models[i]->getPosition()), 1));
        }
        // Load Material Data
        meterialTypeData.push_back(models[i]->getMaterialType());
        materialDiffColorData.push_back(QVector4D(models[i]->getMaterialDiffColorF(), 1));
        materialSpecColorData.push_back(QVector4D(models[i]->getMaterialSpecColorF(), 1));
        materialTransColorData.push_back(QVector4D(models[i]->getMaterialTransColorF()));
        materialLightColorData.push_back(QVector4D(models[i]->getMaterialLightColorF()));
        materialIorData.push_back(models[i]->getMaterialIor());
    }

    // Sphere Radius
    GLuint rad;
    glGenBuffers(1, &rad);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, rad);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float)*radData.size(), &radData[0], GL_STATIC_DRAW); //[0]をつける
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, rad); //binding = 1
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // Sphere Position
    GLuint pos;
    glGenBuffers(1, &pos);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pos);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(QVector4D)*posData.size(), &posData[0], GL_STATIC_DRAW); // Size 変更
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, pos); //binding = 2
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // Material Type
    GLuint materialType;
    glGenBuffers(1, &materialType);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialType);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(int)*meterialTypeData.size(), &meterialTypeData[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, materialType); //binding = 3
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // Diffuse
    GLuint materialDiffColor;
    glGenBuffers(1, &materialDiffColor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialDiffColor);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(QVector4D)*materialDiffColorData.size(), &materialDiffColorData[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, materialDiffColor); //binding = 4
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // Specular
    GLuint materialSpecColor;
    glGenBuffers(1, &materialSpecColor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialSpecColor);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(QVector4D)*materialSpecColorData.size(), &materialSpecColorData[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, materialSpecColor); //binding = 5
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // Transparent
    GLuint materialTransColor;
    glGenBuffers(1, &materialTransColor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialTransColor);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(QVector4D)*materialTransColorData.size(), &materialTransColorData[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, materialTransColor); //binding = 6
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // Light
    GLuint materialLightColor;
    glGenBuffers(1, &materialLightColor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialLightColor);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(QVector4D)*materialLightColorData.size(), &materialLightColorData[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, materialLightColor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    // IOR
    GLuint materialIor;
    glGenBuffers(1, &materialIor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialIor);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float)*materialIorData.size(), &materialIorData[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 8, materialIor);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

    m_vao.release();
}

void RenderWidget::paintGL() {
    // Compute Pathtracing
    m_computeProgram->bind();
    if(frame == 0){
        m_renderProgram->setUniformValue(0, qDegreesToRadians(yRot));
        m_renderProgram->setUniformValue(1, qDegreesToRadians(xRot));
        m_renderProgram->setUniformValue(2, cameraDistance);
        m_renderProgram->setUniformValue(3, RenderMode);
        m_renderProgram->setUniformValue(4, Dof);
    }
    glDispatchCompute(tex_w, tex_h ,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // Draw
    m_renderProgram->bind();
    m_vao.bind();
    glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_SHORT,0);
    m_vao.release();

    if(frame == PassLimit) rendering = false;
    if(rendering) update();
    qDebug() << "Rendering:" <<  ++frame;
}

void RenderWidget::changeRenderMode(const int mode) {
    accumN = 1;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, accum);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned), &accumN, GL_DYNAMIC_COPY);

    RenderMode = mode;

    frame = 0;
    rendering = true;
    update();
}

void RenderWidget::saveImage() {
    rendering = false;
    QString fileName = QFileDialog::getSaveFileName(this, "", "Untitled.png");
    if (!fileName.isEmpty()) grabFramebuffer().save(fileName);
}

void RenderWidget::changeDof(const bool checked){
    accumN = 1;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, accum);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned), &accumN, GL_DYNAMIC_COPY);

    Dof = checked;

    frame = 0;
    rendering = true;
    update();
}

void RenderWidget::resizeGL(int w, int h){
}

// Slots
void RenderWidget::stopRendering() {
    rendering = false;
}
void RenderWidget::startRendering() {
    rendering = true;
    update();
    qDebug() << "Rendering:" <<  ++frame;
}
