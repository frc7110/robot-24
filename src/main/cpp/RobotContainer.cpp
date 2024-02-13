// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/Commands.h>
#include <frc2/command/button/RobotModeTriggers.h>
#include <pathplanner/lib/auto/NamedCommands.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>

#include <memory>
#include <utility>

#include "commands/ShootNote.h"

RobotContainer::RobotContainer() {
  frc::SmartDashboard::PutData("PDP", &m_pdp);
  frc::SmartDashboard::PutData("Auto Chooser", &m_chooser);
  frc::SmartDashboard::PutData("Command Scheduler",
                               &frc2::CommandScheduler::GetInstance());

  frc::SmartDashboard::PutData("Shooter", &m_shooter);
  frc::SmartDashboard::PutData("Arm", &m_arm);

  // Configure the button bindings
  ConfigureDriverButtons();
  ConfigureOperatorButtons();
  ConfigureTriggers();
}

void RobotContainer::ConfigureDriverButtons() {
  m_driverController.A().OnTrue(
      m_shooter.SetTargetStateCMD(ShooterSubsystem::State::kTrapAmp));

  // m_driverController.B().OnTrue(
  //     m_shooter.SetTargetStateCMD(ShooterSubsystem::State::kIdle));

  m_driverController.X().OnTrue(
      m_shooter.SetTargetStateCMD(ShooterSubsystem::State::kStopped));

  // (m_drightTrigger && m_shooter.ShooterReadyTrigger())
  //     .OnTrue(ShootNote(&m_shooter).ToPtr());

  m_driverController.RightBumper()
      .OnTrue(m_shooter.SetFeederCMD(1.0))
      .OnFalse(m_shooter.SetFeederCMD(0));
  m_driverController.LeftBumper()
      .OnTrue(m_shooter.SetFeederCMD(0.25))
      .OnFalse(m_shooter.SetFeederCMD(0));

  m_dleftTrigger.OnTrue(m_intake.SetIntake(0.5)).OnFalse(m_intake.SetIntake(0));
  m_drightTrigger.OnTrue(m_intake.SetIntake(-0.5))
      .OnFalse(m_intake.SetIntake(0));

  m_driverController.Y()
      .OnTrue(m_intake.SetPivot(0.25))
      .OnFalse(m_intake.SetPivot(0));
  m_driverController.B()
      .OnTrue(m_intake.SetPivot(-0.25))
      .OnFalse(m_intake.SetPivot(0));
}

void RobotContainer::ConfigureOperatorButtons() {}

void RobotContainer::ConfigureTriggers() {
    frc2::RobotModeTriggers::Teleop().OnTrue(m_shooter.SetTargetStateCMD(ShooterSubsystem::State::kStopped));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::None();
}
