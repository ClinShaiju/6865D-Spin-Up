#include "main.h"
#include "okapi/impl/util/timer.hpp"
#include "sylib/system.hpp"
#include <type_traits>


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between  
 * "I was pressed!" and nothing.
 */
void on_center_button() {
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	sylib::initialize();

	pros::lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//drive->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

	drive->moveDistance(1_in);
	intake.moveVelocity(-50);
	pros::delay(1000);
	drive->moveDistance(-1_in);

	drive->turnAngle(90_deg);
	targetRPM = globalFlywheelRPM / 7;
	pros::delay(2000);
	indexer.
	

	// drive->turnAngle(90_deg);


	// drive->setMaxVelocity(100);
	// drive->moveDistance(2_ft);
	// drive->turnAngle(-90_deg);
	// drive->moveDistance(2_ft);
	// drive->turnAngle(90_deg);
	// drive->moveDistance(4_ft);

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	//drive->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	drive->setMaxVelocity(200);
	uint32_t clock = sylib::millis();
	Timer Timer_opcontrol = Timer();
	while (true) {
		//Checks if the mod key if active for driver
		isModKey();
		flyPID();
		flyToggle();
		index();
		runIntake();
		endgameExpansion(Timer_opcontrol.millis());
        autoAim(currentAlliancePosition);
		

		double leftY = exponential(controller.getAnalog(ControllerAnalog::leftY));
		double rightX = exponential(controller.getAnalog(ControllerAnalog::rightX));

		//Drive arcade mode
		drive->getModel()->arcade(leftY,rightX);
		//driveOdom.updateState();
		std::cout << driveOdom.getHeading() << std::endl;

		//output info for graphing
		
		//Print flywheel motor value

		sylib::delay_until(&clock, 10);
	}
}
