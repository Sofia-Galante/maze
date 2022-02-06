//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_COORDINATE_H
#define MAZE_COORDINATE_H

class Coordinate{
public:
    Coordinate(int x = 0, int y = 0);
    void setCoordinate(int x, int y);
    int getX(){
        return point[0];
    }
    int getY(){
        return point[1];
    }

    bool operator==(Coordinate &right) const{
        if (point == right.point)
            return true;
        return false;
    }

    bool operator!=(Coordinate &right) {
        if (point == right.point)
            return false;
        return true;
    }

private:
    int point [2];
};

#endif //MAZE_COORDINATE_H
