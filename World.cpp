//
// Created by Daniel Elbaz on 1/23/26.
//

#include "World.h"

void World::AddSceneObject(std::unique_ptr<SceneObject> s) {
    sceneObjects.push_back(std::move(s));
}

void World::AddLight(const Light &l) {
    lights.push_back(l);
}