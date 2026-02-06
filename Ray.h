//
// Created by Daniel Elbaz on 1/26/26.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H



struct cameraValues {
    Vector3 pos;
    Vector3 right;
    Vector3 up;
    Vector3 lookAt;
    int WIDTH;
    int HEIGHT;
    float PIXEL_DISTANCE;
};

struct Ray {
    Vector3 origin;
    Vector3 direction;
    Ray(cameraValues &cv, int xi, int yi) :
    //resets position to 0,0 in world space, then adds the amount of pixels
    //returns a ray in the form of P + tD
    origin(
        cv.pos + (cv.right * -(((cv.WIDTH/2) - xi) * cv.PIXEL_DISTANCE)) + (cv.up * -(((cv.HEIGHT/2) - yi) * cv.PIXEL_DISTANCE))
        ),
    direction(cv.lookAt/sqrt(dot(cv.lookAt, cv.lookAt))) {};

    Ray(Vector3 originParam, Vector3 directionParam) :
    origin(originParam) , direction(directionParam) {};
};


#endif //RAYTRACER_RAY_H