/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#ifndef SLIDEGLWIDGET_H
#define SLIDEGLWIDGET_H

#include <QMainWindow>
#include <QtOpenGL>
#define ROTATION_SPEED (1.0)
#if __linux__
 #include <GL/glut.h>
 #include <GL/gl.h>
 #define ROTATION_SPEED (50.0)
#elif __APPLE__
 #include <GLUT/GLUT.h>
 #define ROTATION_SPEED (1.0)
#endif
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#endif
#include "mesh.h"
#include "makeMesh.h"
#include "polyline.h"
#include "group.h"
#include "makegroup.h"
#include "myselection.h"
#include "subdivison.h"
#include "stl.h"
#include "offset.h"
#include "zipper.h"
#include "parameter.h"
#include "parameterbank.h"
#include <QMessageBox>
#include <QColor>
#include <QString>
#include "newNOME/Session.h"
#include "newNOME/ConsolidateWindow.h"
#include "newNOME/GroupWindow.h"

class SlideGLWidget: public QGLWidget
{
    Q_OBJECT

public:
    explicit SlideGLWidget(QWidget *parent = 0);
    SlideGLWidget(string name, QWidget *parent = 0);
    SlideGLWidget(Group &group, Session *currSession, QWidget *parent = 0);
    ~SlideGLWidget();
    ConsolidateWindow *conWindow;
    GroupWindow *groupWindow;
    void consolidateTempMesh();
    /**
     * Save the current master_mesh in a STL file.
     */
    void saveMesh(string name);
    /**
     * @brief subdivide: for certain level.
     * @param level, level of subdivision.
     */
    void subdivide(int level);
    /**
     * @brief offset: create offset mesh with given value.
     * @param value: the value of this offset.
     */
    void offset(float value);
    /**
     * @brief setForeColor, set default foreground color.
     * @param color, the color to be set.
     */
    void setForeColor(QColor color);
    /**
     * @brief setBackColor, set default background color.
     * @param color, the color to be set.
     */
    void setBackColor(QColor color);

    void setOutsideColor(QColor color);
    void setInsideColor(QColor color);
    void setOffsetColor(QColor color);
    /* The master mesh. As a result of SIF parser. */
    Mesh master_mesh;
    /* The mesh that contains temporary added meshes.*/
    Mesh temp_mesh;
    /* The mesh confirmed by the user and become permenant change. */
    Mesh consolidate_mesh;
    /* The merged result of all meshes in the scene and consolidate mesh. */
    Mesh merged_mesh;
    /* The current subdivided mesh. */
    Mesh subdiv_mesh;
    /* The pointer to the whole scene. */
    Group * hierarchical_scene;
    /* A copy of the hierarchical_scene, with all meshes transformed. */
    Group hierarchical_scene_transformed;
    /* The group from saved consolidate mesh. It is created from aslf file. */
    Group * group_from_consolidate_mesh;

    unordered_map<string, Mesh> meshes;

    /* Update the canvas after reading in the aslf file. */
    void updateFromSavedMesh();
    /* Set the in_editing_mode of scene shown and all leave meshes.*/
    void set_to_editing_mode(bool in_editing_mode);
    /* Record the list of the name of faces deleted by the user.
     * (Not including the consolidated mesh or temprary mesh. */
    vector<string> deletedFaces;
public:
    std::string consolidateMeshName;
    std::string consolidateInstanceName;
    Session *currSession;
    /* Viewer variables.*/
    enum MODES { MODE_OBJECT, MODE_CAMERA, MODE_LIGHT, MODE_LAST } view_mode;
    mat4 transforms[MODE_LAST];
    float cameraDistance;
    float centerX, centerY, centerZ;
    /* Support arcball feature.*/
    int last_mx, last_my, cur_mx, cur_my;
    /* Support arcball feature. */
    int arcball_on;
    /* object2world matrix for arcball.*/
    mat4 object2world;
    /* control of the wireframe mode. */
    bool wireframe;
    /* control of the backface illuminiation. */
    bool backface;
    /* control of the shading mode. */
    bool smoothshading;
    /**
     * @brief makeDefaultMesh: Make a default mesh of a cube.
     */
    void makeDefaultMesh();
    /**
     * @brief makeSIFMesh: Make a mesh by reading in a SIF file.
     * @param name: The path to the input file.
     */
    void makeSIFMesh(string name);
    /**
     * @brief makeSLFMesh: Make a mesh by the output of SLF file parser.
     */
    void makeSLFMesh();
    /* A subdivider to handle subdivision.*/
    Subdivision *subdivider;
    /* An offseter to handle offsetting.*/
    Offset *offseter;
    /**
     * The cache of mesh that has been subdivided.
     * The index in this vector = subdivision level - 1.
     */
    vector<Mesh> cache_subdivided_meshes;
    /* A pointer to the offset mesh. */
    Mesh offset_mesh;
    /* A pointer to the subdivided offset mesh. */
    Mesh subdiv_offset_mesh;
    /*
     * Selection object to handle mouse selection.
     * Only works for interactive editing mode.
     */
    MySelection mySelect;
    /**
     * Get a normalized vector from the center of the virtual ball O to a
     * point P on the virtual ball surface, such that P is aligned on
     * screen's (X,Y) coordinates.  If (X,Y) is too far away from the
     * sphere, return the nearest point on the virtual ball surface.
     */
    vec3 get_arcball_vector(int x, int y);
    /**
     * A wrapper function for selection with mouse
     * @param x, the x coordinate of the mouse clicked
     * @param y, the y coordinate of the mouse clicked
     * @param mode, the mode of selection.
     */
    void mouse_select(int x, int y);
    /**
     * selection_mode = 0: face selection;
     * selection_mode = 1: vertex selection
     * selection_mode = 2: whole border selection (line loop)
     * selection_mode = 3: partial border selection (line strip)
     */
    int selection_mode;
    /* Called by constructor to setup general background parameters. */
    void generalSetup();
    /* A message box that deliver error message.*/
    QMessageBox *errorMsg;
    /* Zoom in in the current view. */
    void zoom_in();
    /* Zoom out in the current view. */
    void zoom_out();
    /*
     * The foreground color.
     */
    QColor foreColor;
    /*
     * The background color.
     */
    QColor backColor;
    QColor outsideColor;
    QColor insideColor;
    QColor offsetColor;
    /*
     * The temp mesh color.
     */
    QColor tempColor;
    /* Auto check if the newly added face can have
     * same orientation with master_mesh. */
    bool auto_check;
    /* Check if whole border selection is on.*/
    bool whole_border;
    /* The zipper.*/
    Zipper *zipper;
    /* The first border to zip.*/
    PolyLine border1;
    /* The second border to zip. */
    PolyLine border2;
    /**
     * @brief clearSubDivisionAndOffset: Clear the subdiv_mesh
     * and offset_mesh.
     */
    void clearSubDivisionAndOffset();
    /**
     * @brief clearSelection: clear the selected items.
     */
    void clearSelection();
    /* A flattened view of meshes in the current scene. */
    vector<Mesh*> global_mesh_list;
    /* A flattened view of polylines in the current scene. */
    vector<PolyLine*> global_polyline_list;
    /* Index list of where the name buffer start for every mesh.*/
    vector<int> global_name_index_list;
    /* Index list of where the name buffer start for every polyline.*/
    vector<int> global_polyline_name_index_list;
    /* Update the global name index list.*/
    void updateGlobalIndexList();
    /* A wrapper class to draw the whole scene.
     * The drawing result depends on the viewer_mode.
     */
    void draw_scene();
    /* The trianglePanelty for zipping function. */
    float trianglePanelty;
    /* Create the hierarchical_scene_transformed. */
    void transform_meshes_in_scene();
    /* The current mode of view.
     * 1: Hierarchical Scene.
     * SLF will read in the scene with parameters set up.
     * SIF will read in just one mesh.
     * This is the interactive editing mode.
     * 2: Merged Modified Mesh
     * This is the merged result of the modified mesh. It is a perfect
     * 2-manifold to serve as the input of the subdivision.
     * 3: Subdivied Mesh
     * 4: Offseted Mesh
     */
    int viewer_mode;
    /* A wrapper function to draw the viewed mesh. */
    void draw_mesh(int start_index, Mesh *mesh);
    /* A wrapper function to draw the viewed polyline. */
    void draw_polyline(int start_index, PolyLine *polyline);
    /* Current work phase. */
    int work_phase;
    /* The current subdivision level.*/
    int subdiv_level;
    /* The current offset value. */
    float offset_value;
    /* Merge all meshes from global_mesh_list into master_mesh.*/
    void mergeAll();
    /* Update the temprary mesh.*/
    void updateTempMesh();
    /* Update the consolidate mesh.*/
    void updateConsolidateMesh();
    /* Update the saved consolidated mesh. */
    void updateSavedConsolidatedMesh();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintGLImpl();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    /**
     * @brief timerEvent: Timer Event for this MainWindow.
     * Similar to OnIdleFunc of GLUT.
     */
    void timerEvent(QTimerEvent *event);
    /**
     * @brief wheelEvent: Handles mouse wheel event.
     * Will zoom in or zoom out in the scene.
     * @param event: The qt wheel event.
     */
    void wheelEvent(QWheelEvent *event);
public slots:
    /**
     * @brief viewContentChanged: Change the current view mesh.
     * @param viewer_mode, the mode for the viewer.
     */

    void createConsolidated(bool);
    void readConsolidateMeshName(QString text);
    void readConsolidateInstanceName(QString text);
    void viewContentChanged(int viewer_mode);
    /* Receive the signal from control panel to do subdivision.*/
    void levelChanged(int);
    /* Receive the signal to reset the viewing direction. */
    void resetViewDirection(bool);
    /* Receive the signal of offset value changed. */
    void offsetValueChanged(float);
    /* Recevie the signal of changing to vertex selection mode. */
    void vertexModeChecked(bool);
    /* Recevie the signal of changing to border selection mode. */
    void borderModeChecked(bool);
    /* Recevie the signal of changing to face selection mode. */
    void faceModeChecked(bool);
    /* Receive the signal auto correct orientation in adding mode. */
    void autoCorrectChecked(bool);
    void repaintCanvas();
    /* Receive the signal whole border selection in zipping mode. */
    void wholeBorderSelectionChecked(bool);
    /* Receive the signal to add a polygon to temp_mesh. */
    void addToTempCalled(bool);
    void groupFacesMsg(bool);
    void undoFaceCalled(bool);
    void addToPolylineCalled(bool);
    /* Receive the signal to zip two borders.
     * And add the result polygons to temp_mesh. */
    void zipToTempCalled(bool);
    /* Recieve signal to add the temp_mesh to master_mesh.*/
    void addTempToMasterCalled(bool);
    /* Recieve signal to add the temp_mesh to consolidated_mesh. */
    void popUpConsolidateWindow(bool);

    void popUpGroupWindow(bool);
    /* Add temp_mesh to master_mesh. */
    void addTempToMaster();
    /* Receive the signal to add a border. Add border1 first*/
    void addBorderCalled(bool);
    /* Receive the signal to clear all selections.
     * Including selected vertices and border. */
    void clearSelectionCalled(bool);
    /* Reset the triangle panelty of zipping function. */
    void resetTrianglePanelty(QString);
    /* @brief mergeCalled: Recieve the signal from control panel to merge. */
    void mergeCalled(bool);
    /* Slider value changed.*/
    void paramValueChanged(float);
    /* Delete the selected faces called. */
    void deleteFaceCalled(bool);
signals:
    /* A feedback signal send back to control panel statusBar.*/
    void feedback_status_bar(QString, int);
};

#endif // SLIDEGLWIDGET_H
