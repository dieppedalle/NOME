#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T18:34:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NOME
TEMPLATE = app
CONFIG += c++11
CONFIG += static
CONFIG += console

SOURCES += main.cpp\
    edge.cpp \
    vertex.cpp \
    face.cpp \
    mesh.cpp \
    polyline.cpp \
    merge.cpp \
    transformation.cpp \
    makeMesh.cpp \
    subdivision.cpp \
    offset.cpp \
    stl.cpp \
    zipper.cpp \
    makePolyline.cpp \
    myselection.cpp \
    controlpanel.cpp \
    mainwindow.cpp \
    group.cpp \
    makegroup.cpp \
    sliderpanel.cpp \
    parameter.cpp \
    myslider.cpp \
    parameterbank.cpp \
    utils.cpp \
    nomeparser.cpp \
    nomeglwidget.cpp \
    bspline.cpp \
    newNOME/Data.cpp \
    newNOME/IO.cpp \
    newNOME/Reader.cpp \
    newNOME/Session.cpp \
    testpolyline.cpp \
    newNOME/GroupNew.cpp \
    newNOME/InstanceNew.cpp \
    newNOME/MeshNew.cpp \
    newNOME/Node.cpp \
    newNOME/TransformationNew.cpp \
    newNOME/BankNew.cpp \
    newNOME/SliderNew.cpp \
    newNOME/PolylineNew.cpp \
    newNOME/CircleNew.cpp \
    newNOME/FunnelNew.cpp \
    newNOME/TunnelNew.cpp \
    newNOME/ConsolidateWindow.cpp \
    newNOME/SubdivisionNew.cpp \
    newNOME/SliderSubdivisionNew.cpp \
    newNOME/OffsetNew.cpp \
    newNOME/SliderOffsetNew.cpp \
    nomeFlexBison.cpp \
    compilerNome/parser.cpp \
    compilerNome/lexer.cpp \
    stlFlexBison.cpp \
    compilerStl/parserStl.cpp \
    compilerStl/lexerStl.cpp \
    newNOME/BSplineNew.cpp \
    newNOME/BezierCurveNew.cpp \
    objFlexBison.cpp \
    compilerObj/parserObj.cpp \
    compilerObj/lexerObj.cpp \
    compilerBank/parserBank.cpp \
    compilerBank/lexerBank.cpp \
    bankFlexBison.cpp \
    newNOME/GroupWindow.cpp \
    Math/AreaAllocator.cpp \
    Math/BoundingBox.cpp \
    Math/Color.cpp \
    Math/Frustum.cpp \
    Math/MathDefs.cpp \
    Math/Matrix2.cpp \
    Math/Matrix3.cpp \
    Math/Matrix3x4.cpp \
    Math/Matrix4.cpp \
    Math/Plane.cpp \
    Math/Polyhedron.cpp \
    Math/Quaternion.cpp \
    Math/Random.cpp \
    Math/Ray.cpp \
    Math/Rect.cpp \
    Math/Sphere.cpp \
    Math/StringHash.cpp \
    Math/Vector2.cpp \
    Math/Vector3.cpp \
    Math/Vector4.cpp \
    newNOME/Octree.cpp \
    newNOME/OctreeProxy.cpp


HEADERS  += \
    edge.h \
    vertex.h \
    face.h \
    mesh.h \
    polyline.h \
    transformation.h \
    merge.h \
    makeMesh.h \
    subdivison.h \
    offset.h \
    stl.h \
    zipper.h \
    makePolyline.h \
    myselection.h \
    controlpanel.h \
    mainwindow.h \
    group.h \
    makegroup.h \
    sliderpanel.h \
    parameter.h \
    myslider.h \
    parameterbank.h \
    utils.h \
    nomeparser.h \
    nomeglwidget.h \
    bspline.h \
    newNOME/Data.h \
    newNOME/IO.h \
    newNOME/Reader.h \
    newNOME/Session.h \
    testpolyline.h \
    newNOME/GroupNew.h \
    newNOME/InstanceNew.h \
    newNOME/MeshNew.h \
    newNOME/Node.h \
    newNOME/TransformationNew.h \
    newNOME/BankNew.h \
    newNOME/SliderNew.h \
    newNOME/PolylineNew.h \
    newNOME/CircleNew.h \
    newNOME/FunnelNew.h \
    newNOME/TunnelNew.h \
    newNOME/ConsolidateWindow.h \
    newNOME/SubdivisionNew.h \
    newNOME/SliderSubdivisionNew.h \
    newNOME/OffsetNew.h \
    newNOME/SliderOffsetNew.h \
    compilerNome/parser.hpp \
    compilerStl/parserStl.hpp \
    newNOME/BSplineNew.h \
    newNOME/BezierCurveNew.h \
    compilerObj/parserObj.hpp \
    compilerBank/parserBank.hpp \
    newNOME/GroupWindow.h \
    Math/AreaAllocator.h \
    Math/BoundingBox.h \
    Math/Color.h \
    Math/Frustum.h \
    Math/MathAPI.h \
    Math/MathDefs.h \
    Math/Matrix2.h \
    Math/Matrix3.h \
    Math/Matrix3x4.h \
    Math/Matrix4.h \
    Math/Plane.h \
    Math/PODVector.h \
    Math/Polyhedron.h \
    Math/Quaternion.h \
    Math/Random.h \
    Math/Ray.h \
    Math/Rect.h \
    Math/Sphere.h \
    Math/StringHash.h \
    Math/Vector2.h \
    Math/Vector3.h \
    Math/Vector4.h \
    newNOME/Octree.h \
    newNOME/OctreeProxy.h

INCLUDEPATH += ./Math
DEFINES += TC_USE_SSE

linux{
    LIBS += -lglut -lGLU
}

mac{
    INCLUDEPATH += /usr/local/include
    LIBS += -framework GLUT -framework OpenGL
}

win32{
    LIBS += -lopengl32 -lglu32 -lglut32
    INCLUDEPATH += $$PWD/../include
    RC_ICONS += nomeIcon.ico
    QMAKE_CXXFLAGS +=-msse3
}
