#ifndef UMJAHO_CAR_H
#define UMJAHO_CAR_H

#include <vector>

#include "engine/scenes/SceneElement.h"
#include "engine/Renderer.h"
#include "engine/scenes/scenes/Checkpoint.h"

class Car : public SceneElement {
	public:
		static const double WIDTH;
		static const double LENGTH;
	    static const double NITRO_MULTIPLIER;
	    static const int NEEDED_CHARGES;
	    static const int NITRO_TIME;
		static const double BRAKE_STRENGTH;
		static const double TURN_GAIN;
		static const double ACCELERATION;
		static const double MAX_SPEED;
		static const double MAX_TURN_ANGLE;

	    double acceleration = 0.02;
	    double speed = 0.0;
	    double maxSpeed = 4;

		double brakeStrength = 0.05;

		double turnGain = 0.001;
	    double turnAngle = 0.0;     // Current angle of the wheels in radians
		double maxTurnAngle = 0.03; // Max angle of the wheels
	
		bool canMove = true;
        int nextCheckpoint;
        int totalCheckpoints;

	    Car(double x, double y, int next = 0, int totalCheckpoints = -1, double width = Car::WIDTH, double length = Car::LENGTH,
            double angle = 0,
            double zIndex = 0, SDL_Texture *texture = nullptr);
		bool onCurb = false;
		bool onDirt = false;
		bool onIce = false;

		Uint64 lastWaterTime = -1000;
		Uint64 lastOilTime = -1000;

	    Car(double x, double y, double width = WIDTH, double length = LENGTH, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
	    void move();
	    void decelerate();
	    void accelerate();
	    void brake();
	    void reverse();
	    void turnLeft();
	    void turnRight();
	    void straighten();
		void collide(SceneElement* element) override;
		void resetStats();

		void enterCurb();
		void leaveCurb();
		void enterDirt();
		void enterIce();
		void leaveDirt();
		void leaveIce();
};

#endif //UMJAHO_CAR_H
