//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_COORDINATE_H
#define MAZE_COORDINATE_H

class Coordinate{
public:
    Coordinate(int x = 0, int y = 0);
    void setCoordinate(int x, int y);
    void setCoordinate(Coordinate p){
        setCoordinate(p.getX(), p.getY());
    }
    int getX(){
        return point[0];
    }
    int getY(){
        return point[1];
    }

    bool operator==(const Coordinate &right) const{
        if (point[0] != right.point[0])
            return false;
        if (point[1] != right.point[1])
            return false;
        return true;
    }


    bool operator!=(const Coordinate &right) const{
        if (point[0] != right.point[0])
            return true;
        if (point[1] != right.point[1])
            return true;
        return false;
    }

private:
    int point [2];
};

#endif //MAZE_COORDINATE_H
