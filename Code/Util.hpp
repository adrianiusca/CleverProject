#pragma once

// standard libraries
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <functional>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <chrono>
#include <experimental/filesystem>

// graphic libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// glm mathematics 
#define GLM_FORCE_INLINE

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

// importers
#include <FreeImage.h>

using namespace glm;
using namespace std;

using namespace std::chrono;
using namespace std::experimental::filesystem;