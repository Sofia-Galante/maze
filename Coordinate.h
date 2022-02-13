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
        return x;
    }
    int getY(){
        return y;
    }

    bool operator==(const Coordinate &right) const{
        if (x != right.x)
            return false;
        if (y != right.y)
            return false;
        return true;
    }


    bool operator!=(const Coordinate &right) const{
        if (x != right.x)
            return true;
        if (y != right.y)
            return true;
        return false;
    }

private:
    int x;
    int y;
};

#endif //MAZE_COORDINATE_H
