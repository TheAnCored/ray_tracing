#include <array>
#include <cmath>
#include <sstream>
#include <fstream>

#include "Sphere.h"
//#include "Cuboid.h"
#include "Kinescope.h"
#include "Figure.h"
#include "Tetrahedron.h"

#include "autotests.h"

// Чтение характеристик сцены
Kinescope reading_scene(std::string&);

// Чтение фигур из файла
std::vector<std::shared_ptr<Figure>> reading_figures(std::string&);