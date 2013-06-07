#pragma once
#include "StarlabDrawArea.h"

typedef Eigen::Vector3d Vector3;
typedef Eigen::Hyperplane<double,3> Plane3;
typedef Eigen::ParametrizedLine<double,3> Ray3;

class Controller : public QObject{  
    Q_OBJECT
    
    enum NAMES {SPHERE,XAXIS,YAXIS,ZAXIS};
    
    friend class ControllerManager;
    bool _selected;
    Vector3 center;
    
    /// Not null when ControllerManager->add(this)
    StarlabDrawArea* drawArea;
    
    /// Reference frame 
    Eigen::Matrix3d frame;

    /// Controls editing    
    Plane3  pan_hyperplane;
    Vector3 click_origin;
    Vector3 center_before;
    int selected_subcomponent;

private:
    Plane3 xy_plane(){
        return Plane3(frame.col(3),center);
    }
    Ray3 x_ray(){ 
        return Ray3(center,frame.col(1));   
    }
    
public:   
    Controller(Vector3 center):
        center(center){
        _selected = false;
        selected_subcomponent = -1;        
        /// Init reference frame
        frame.setIdentity(3,3);
    }
      
    // picking with LINE/POINT does not work well :( :(
    // glBegin(GL_LINES); glVertex3d(0,0,0); glVertex3d(1.0,0,0); glEnd();            
    void draw(){
        static GLUquadric* quadric = gluNewQuadric();
        glColor3f(0.8,0.8,0.8);
        glPushMatrix();
            glTranslated(center[0], center[1], center[2]);
            /// Sphere
            gluSphere(quadric, 0.1, 10, 10);
            /// X-axis
            glRotated(90,0,1,0); 
            gluCylinder(quadric,.05, .05, 1, 5, 1);
        glPopMatrix();
    }
       
    void draw_with_names(){
        static GLUquadric* quadric = gluNewQuadric();
        glColor3f(0.8,0.8,0.8);
        glInitNames();
        glPushMatrix();
            glTranslated(center[0], center[1], center[2]);
            /// Sphere
            glPushName(SPHERE);
                gluSphere(quadric, 0.1, 10, 10);
            glPopName();
            /// X-axis
            glPushName(XAXIS);
                glRotated(90,0,1,0); 
                gluCylinder(quadric,.05, .05, 1, 5, 1);
            glPopName();    
        glPopMatrix();
    }
    
    void mousePressEvent(QMouseEvent* event){
        // qDebug() << "mousePressEvent";
        /// When clicking on sphere
        QPoint p = event->pos();
        Vector3 orig, dir;
        drawArea->convert_click_to_line(p, orig, dir);
        Ray3 ray(orig,dir);
        
        /// cache original position
        center_before = center;

        /// Compute transformation space
        pan_hyperplane = Plane3(dir,center);
        click_origin = ray.intersectionPoint(pan_hyperplane);
        
        
    
        // drawArea->drawPoint(click_origin).size(15).color(Qt::red);
        // drawArea->updateGL();
        // return;
    }
    
    void mouseMoveEvent(QMouseEvent* event){
        // qDebug() << "mouseMoveEvent";        
        QPoint p = event->pos();
        Vector3 orig, dir;
        drawArea->convert_click_to_line(p, orig, dir);
        Ray3 ray(orig,dir);
        
        switch(selected_subcomponent){
        case XAXIS: 
            // Vector3 ixy = ray.intersectionPoint(xy_plane);
            
            
            qDebug() << "should move only in his direction";
            break;
        
            
            
        case SPHERE:
        default: 
            Vector3 curr_isect = ray.intersectionPoint(pan_hyperplane);        
            Vector3 offset = curr_isect - click_origin;
            center = center_before + offset; 
            break;
        }
        
        /// Update the visualization
        drawArea->updateGL();
    }
};

class ControllerManager{
private:
    StarlabDrawArea* drawArea;
    QList<Controller*> _list;
    /// Might be null when nothing is selected
    Controller* _selected;
    
public:
    ControllerManager(StarlabDrawArea* drawArea) :
        drawArea( drawArea ){
        _selected = NULL;
    }
    
    void add(Controller* c){
        c->drawArea = drawArea;
        _list.push_back(c);
    }

    void draw(){
        glLineWidth(100);
        glEnable(GL_LIGHTING);
        foreach(Controller* c, _list)
            c->draw();
    }
    
    void draw_with_names(){
        // qDebug() << "ControllerManager::draw_with_names()";
        /// Clears the name buffer
        if(_selected==NULL){
            qDebug() << "drawing main component names";
            glInitNames();
            int i=0;
            foreach(Controller* c, _list){
                glPushName(i++);
                    c->draw();                    
                glPopName();
            }
        } else {
            qDebug() << "drawing sub component names";
            _selected->draw_with_names();            
        }
    }
    
    void mousePressEvent(QMouseEvent* event){
        QPoint pickpoint = event->pos();
        
        /// Fetch the controller
        _selected = NULL;
        drawArea->select(pickpoint); 
        // call to "draw_with_names()" is made
        int offset = drawArea->selectedName();
        qDebug() << "Selected controller #:" << offset;        
        if( offset>=0 && offset<_list.size() ){
            _selected = _list.at(offset);
        }
                
        /// Attempt identify sub-controller
        if(_selected!=NULL){
            drawArea->select(pickpoint);
            // call to "draw_with_names()" is made
            int offset = drawArea->selectedName();
            qDebug() << "Sub-controller #:" << offset;
            _selected->selected_subcomponent = offset;
        }

        /// Pass even to the controller itself
        if(_selected!=NULL)
            _selected->mousePressEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent* event){
        
    }
    void mouseMoveEvent(QMouseEvent* event){
        if(_selected!=NULL){
            _selected->mouseMoveEvent(event);   
        }
    }
};
