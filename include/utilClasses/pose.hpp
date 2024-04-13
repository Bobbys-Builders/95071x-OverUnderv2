// #ifndef POSE_HPP
// #define POSE_HPP

// #include "main.h"
// #include "okapi/api/units/RQuantity.hpp"

// class Pose {
// public:
//     // Variables

//     double x = 0;
//     double y = 0;
//     double h = 0;

//     // Constructors
//     Pose() {}
//     Pose(double x, double y) : x(x), y(y) {}
//     Pose(double x, double y, double h)
//         : x(x), y(y), h(h) {}
//     // Update pid error
//     void update(double x, double y, double h) {
//         this->x=x;
//         this->y=y;
//         this->h=h;
//     }

//     double toRad(double input) { return input * M_PI/180; }
//     double toDeg(double input) { return input * 180/M_PI; }
    
//     double sign(double input) {
//         if (input == 0) return 1;
//         return fabs(input) / input;
//     }

//     /**
//      * @brief Add a pose to this pose
//      *
//      * @param other other pose
//      * @return Pose
//      */
//     Pose Pose::operator+(const Pose& other) {
//         return Pose(this->x + other.x, this->y + other.y, this->h);
//     }

//     /**
//      * @brief Subtract a pose from this pose
//      *
//      * @param other other pose
//      * @return Pose
//      */
//     Pose Pose::operator-(const Pose& other) {
//         return Pose(this->x - other.x, this->y - other.y, this->h);
//     }

//     /**
//      * @brief Multiply a pose by this pose
//      *
//      * @param other other pose
//      * @return Pose
//      */
//     double Pose::operator*(const Pose& other) { return this->x * other.x + this->y * other.y; }

//     /**
//      * @brief Multiply a pose by a double
//      *
//      * @param other double
//      * @return Pose
//      */
//     Pose Pose::operator*(const double& other) {
//         return Pose(this->x * other, this->y * other, this->h);
//     }

//     /**
//      * @brief Divide a pose by a double
//      *
//      * @param other double
//      * @return Pose
//      */
//     Pose Pose::operator/(const double& other) {
//         return Pose(this->x / other, this->y / other, this->h);
//     }

//     /**
//      * @brief Linearly interpolate between two poses
//      *
//      * @param other the other pose
//      * @param t t value
//      * @return Pose
//      */
//     Pose Pose::lerp(Pose other, double t) {
//         return Pose(this->x + (other.x - this->x) * t, this->y + (other.y - this->y) * t, this->h);
//     }

//     // /**
//     //  * @brief Get the distance between two poses
//     //  *
//     //  * @param other the other pose
//     //  * @return double
//     //  */
//     // double Pose::distance(Pose other) const { return std::hypot(this->x - other.x, this->y - other.y); }

//     // /**
//     //  * @brief Get the angle between two poses
//     //  *
//     //  * @param other the other pose
//     //  * @return double in radians
//     //  */
//     // double Pose::angle(Pose other) const { return std::atan2(other.y - this->y, other.x - this->x); }
// };

// #endif