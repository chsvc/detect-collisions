#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <random>

using namespace std;


class Circle {
private:
    float _radius;
    vector<float> _velocity;
    vector<float> _coordinates;

public:
    Circle(float _radius, vector<float> _velocity, vector<float> _coordinates) {
        this->_radius = _radius;
        this->_velocity = _velocity;
        this->_coordinates = _coordinates;
    }

    vector<float> getVelocity() {
        return this->_velocity;
    }

    vector<float> getCoordinates() {
        return this->_coordinates;
    }

    float getRadius () const {
        return this->_radius;
    }

    void setVelocityX(float x_velocity) {
        this->_velocity.at(0) = x_velocity;
    }

    void setVelocityY(float y_velocity) {
        this->_velocity.at(1) = y_velocity;
    }

    void setCoordinateX(float x_coordinate) {
        this->_coordinates.at(0) = x_coordinate;
    }

    void setCoordinateY(float y_coordinate) {
        this->_coordinates.at(1) = y_coordinate;
    }
};


class Box {
private:
    float _x_coord;
    float _y_coord;
    float _width;
    float _height;
    vector<Circle*> _vectorOfBalls;

public:
    Box(float x_coord, float y_coord, float width, float height) {
        this->_x_coord = x_coord;
        this->_y_coord = y_coord;
        this->_width = width;
        this->_height = height;
    }


    vector<Circle*> getVectorOfBalls() {
        return this->_vectorOfBalls;
    }

    void pushToVectorOfBalls(Circle* circle) {
        this->_vectorOfBalls.push_back(circle);
    }

    float getXCoord() {
        return this->_x_coord;
    }

    float getYCoord() {
        return this->_y_coord;
    }

    float getWidth() {
        return this->_width;
    }

    float getHeight() {
        return this->_height;
    }

    bool isContains(Circle* circle) {
        if ((circle->getCoordinates().at(0) <= this->_x_coord + this->_width / 2 &&
             circle->getCoordinates().at(0) >= this->_x_coord - this->_width / 2) &&
            (circle->getCoordinates().at(1) <= this->_y_coord + this->_height / 2 &&
             circle->getCoordinates().at(1) >= this->_y_coord - this->_height / 2)) {
            return true;
        }else {return false;}
    }
};


class Plane {
private:
    float _width;
    float _height;
    vector<float> _coordinates;

public:
    Plane(float width, float height) {
        this->_width = width;
        this->_height = height;
        this->_coordinates.push_back(this->_width / 2);
        this->_coordinates.push_back(this->_height / 2);
    }

    float getWidth() {
        return this->_width;
    }

    float getHeight() {
        return this->_height;
    }

    float getXCoordinate() {
        return this->_coordinates.at(0);
    }

    float getYCoordinate() {
        return this->_coordinates.at(1);
    }
};


class Node {
private:
    Box* _box;
    Node* _parent;
    Node* _bottom_left;
    Node* _bottom_right;
    Node* _top_left;
    Node* _top_right;
    vector<Circle*> _circles;
    static const int _capacity = 4;
    bool _is_divided = false;

public:
    Node(Box* box, Node* parent, Node* bottom_left, Node* bottom_right, Node* top_left, Node* top_right) {
        this->_parent = parent;
        this->_bottom_left = bottom_left;
        this->_bottom_right = bottom_right;
        this->_top_left = top_left;
        this->_top_right = top_right;
        this->_box = box;
    }

    ~Node() {
        delete this->_top_right;
        delete this->_top_left;
        delete this->_bottom_right;
        delete this->_bottom_left;
        delete this->_box;
    }

    int getCapacity() {
        return _capacity;
    }

    bool getIsDivided() {
        return this->_is_divided;
    }

    Box* getBox() {
        return this->_box;
    }

    Node* getParent() {
        return this->_parent;
    }

    Node* getBottomLeft() {
        return this->_bottom_left;
    }

    Node* getBottomRight() {
        return this->_bottom_right;
    }

    Node* getTopLeft() {
        return this->_top_left;
    }

    Node* getTopRight() {
        return this->_top_right;
    }

    vector<Circle*> getCircles() {
        return this->_circles;
    }

    void pushCircle(Circle* circle) {
        this->_circles.push_back(circle);
    }

    void setBottomLeft(Node* new_bottom_left) {
        this->_bottom_left = new_bottom_left;
    }

    void setBottomRight(Node* new_bottom_right) {
        this->_bottom_right = new_bottom_right;
    }

    void setTopLeft(Node* new_top_left) {
        this->_top_left = new_top_left;
    }

    void setTopRight(Node* new_top_right) {
        this->_top_right = new_top_right;
    }

    void setIsDivided(bool state) {
        this->_is_divided = state;
    }
};


class QuadTree {
private:
    Node* _root;
public:

    QuadTree(Node* rootNode) {
        this->_root = rootNode;
    }

    ~QuadTree() {
        delete this->_root;
    }

    Node* getRoot() {
        return this->_root;
    }

    bool isCollision(Circle* circle1, Circle* circle2) {
        float distance = sqrt(pow(circle1->getCoordinates().at(0) - circle2->getCoordinates().at(0), 2) +
                              pow(circle1->getCoordinates().at(1) - circle2->getCoordinates().at(1), 2));
        return distance <= (circle1->getRadius() + circle2->getRadius());
    }

    void swapVelocities(Circle* circle1, Circle* circle2) {
        float velocity;
        velocity = circle1->getVelocity().at(0);
        circle1->setVelocityX(circle2->getVelocity().at(0));
        circle2->setVelocityX(velocity);
        velocity = circle1->getVelocity().at(1);
        circle1->setVelocityY(circle2->getVelocity().at(1));
        circle2->setVelocityY(velocity);
        if (circle1->getVelocity().at(1) == 0 && circle2->getVelocity().at(0) == 1) {
            circle1->setCoordinateX(circle1->getCoordinates().at(0) + (circle1->getVelocity().at(0) / abs(circle1->getVelocity().at(0))));
            circle2->setCoordinateX(circle2->getCoordinates().at(0) + (circle2->getVelocity().at(0) / abs(circle2->getVelocity().at(0))));
        } else if (circle1->getVelocity().at(0) == 0 && circle2->getVelocity().at(0) == 0) {
            circle1->setCoordinateY(circle1->getCoordinates().at(1) + (circle1->getVelocity().at(1) / abs(circle1->getVelocity().at(1))));
            circle2->setCoordinateY(circle2->getCoordinates().at(1) + (circle2->getVelocity().at(1) / abs(circle2->getVelocity().at(1))));
        } else {
            circle1->setCoordinateX(circle1->getCoordinates().at(0) + (circle1->getVelocity().at(0) / abs(circle1->getVelocity().at(0))));
            circle2->setCoordinateX(circle2->getCoordinates().at(0) + (circle2->getVelocity().at(0) / abs(circle2->getVelocity().at(0))));
            circle1->setCoordinateY(circle1->getCoordinates().at(1) + (circle1->getVelocity().at(1) / abs(circle1->getVelocity().at(1))));
            circle2->setCoordinateY(circle2->getCoordinates().at(1) + (circle2->getVelocity().at(1) / abs(circle2->getVelocity().at(1))));
        }
    }

    void isEdgeCollision(Circle* circle, Plane* plane) {
        if ((circle->getCoordinates().at(0) + circle->getRadius() >= (plane->getXCoordinate() + plane->getWidth() / 2) ||
             circle->getCoordinates().at(0) - circle->getRadius() <= (plane->getXCoordinate() - plane->getWidth() / 2))) {
            circle->setVelocityX(- circle->getVelocity().at(0));
            circle->setCoordinateX(circle->getCoordinates().at(0) + (circle->getRadius() * circle->getVelocity().at(0) / abs(circle->getVelocity().at(0))));
            return;
        }
        if ((circle->getCoordinates().at(1) + circle->getRadius() >= (plane->getYCoordinate() + plane->getHeight() / 2) ||
             circle->getCoordinates().at(1) - circle->getRadius() <= (plane->getYCoordinate() - plane->getHeight() / 2))) {
            circle->setVelocityY(- circle->getVelocity().at(1));
            circle->setCoordinateY(circle->getCoordinates().at(1) + (circle->getRadius() * circle->getVelocity().at(1) / abs(circle->getVelocity().at(1))));
            return;
        } else {
            return;
        }
    }

    void orderTravers(Node* node, Plane* plane) {
        if (!node->getIsDivided()) {
            for (Circle *circle1: node->getCircles()) {
                isEdgeCollision(circle1, plane);
                for (Circle *circle2: node->getCircles()) {
                    if (circle1 != circle2) {
                        if (isCollision(circle1, circle2)) {
                            swapVelocities(circle1, circle2);
                        }
                    }
                }
            }
            return;
        } else {
            orderTravers(node->getBottomRight(), plane);
            orderTravers(node->getBottomLeft(), plane);
            orderTravers(node->getTopRight(), plane);
            orderTravers(node->getTopLeft(), plane);
        }
    }

    bool insert(Circle* circle, Node* node) {
        if (!node->getBox()->isContains(circle)) {
            return false;
        }
        if (node->getCircles().size() < node->getCapacity()) {
            node->pushCircle(circle);
            return true;
        } else {
            if (!node->getIsDivided()) {
                subdivide(node);
                for (Circle* circle0 : node->getCircles()) {
                    if (insert(circle0, node->getTopLeft())) {
                        continue;
                    } else if (insert(circle0, node->getTopRight())) {
                        continue;
                    } else if (insert(circle0, node->getBottomLeft())) {
                        continue;
                    } else if (insert(circle0, node->getBottomRight())) {
                        continue;
                    }
                }
            }
            if(insert(circle, node->getTopLeft())) {return true;}
            if(insert(circle, node->getTopRight())) {return true;}
            if(insert(circle, node->getBottomLeft())) {return true;}
            if(insert(circle, node->getBottomRight())) {return true;}
        }
    }

    void subdivide(Node* node) {
        node->setBottomLeft(new Node(new Box(node->getBox()->getXCoord() - (node->getBox()->getWidth() / 4),
                                             node->getBox()->getYCoord() - (node->getBox()->getHeight() / 4),
                                             node->getBox()->getWidth() / 2, node->getBox()->getHeight() / 2),
                                     node, nullptr, nullptr, nullptr, nullptr));
        node->setBottomRight(new Node(new Box(node->getBox()->getXCoord() + (node->getBox()->getWidth() / 4),
                                              node->getBox()->getYCoord() - (node->getBox()->getHeight() / 4),
                                              node->getBox()->getWidth() / 2, node->getBox()->getHeight() / 2),
                                      node, nullptr, nullptr, nullptr, nullptr));
        node->setTopLeft(new Node(new Box(node->getBox()->getXCoord() - (node->getBox()->getWidth() / 4),
                                          node->getBox()->getYCoord() + (node->getBox()->getHeight() / 4),
                                          node->getBox()->getWidth() / 2, node->getBox()->getHeight() / 2),
                                  node, nullptr, nullptr, nullptr, nullptr));
        node->setTopRight(new Node(new Box(node->getBox()->getXCoord() + (node->getBox()->getWidth() / 4),
                                           node->getBox()->getYCoord() + (node->getBox()->getHeight() / 4),
                                           node->getBox()->getWidth() / 2, node->getBox()->getHeight() / 2),
                                   node, nullptr, nullptr, nullptr, nullptr));
        node->setIsDivided(true);
    }
};




int main() {
    Plane* plane = new Plane(500, 500);
    Box* rootBox = new Box(plane->getXCoordinate(), plane->getYCoordinate(), plane->getWidth(), plane->getHeight());
    Node* rootNode = new Node(rootBox, nullptr, nullptr, nullptr, nullptr, nullptr);
    QuadTree* tree = new QuadTree(rootNode);
    vector<Circle*> vecOfCircles;
    for(int i=1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            int num1 = 1 + rand()%10;
            int num2 = 1 + rand()%10;
            Circle* circle1 = new Circle(10, {static_cast<float>(15*pow(-1,num1)), static_cast<float>(15*pow(-1,num2))}, {static_cast<float>(45*i), static_cast<float>(45*j)});
            vecOfCircles.push_back(circle1);
        }
    }
    for (Circle* circle : vecOfCircles) {
        tree->insert(circle, rootNode);
    }


    float t = 0;
    float dt = 0.1;

    while(t < 100) {
        tree->orderTravers(tree->getRoot(), plane);

        for(Circle* circle : vecOfCircles) {
            circle->setCoordinateX(circle->getCoordinates().at(0) + circle->getVelocity().at(0) * dt);
            circle->setCoordinateY(circle->getCoordinates().at(1) + circle->getVelocity().at(1) * dt);
        }
        t += dt;

        //rootNode можно не удалять, так как это делает деструктор после того, как старый rootNode выходит из области видимости

        rootNode = new Node(rootBox, nullptr, nullptr, nullptr, nullptr, nullptr);
        QuadTree* tree1 = tree;
        tree = new QuadTree(rootNode);
        delete tree1;


        for (Circle* circle : vecOfCircles) {
            cout << circle->getCoordinates().at(0) << "," << circle->getCoordinates().at(1) << "," << circle->getRadius() << ","  << t << endl;
            tree->insert(circle, rootNode);

        }
    }
    delete tree;
    delete rootNode;
    delete rootBox;
    delete plane;
    return 0;
}