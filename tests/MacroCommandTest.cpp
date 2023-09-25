#include "Commands/MacroCommand/MacroCommand.h"
#include "Commands/CheckFuel/CheckFuel.h"
#include "Adapters/FuelAdapters/CheckFuelAdapter.h"
#include "Commands/BurnFuel/BurnFuel.h"
#include "Adapters/FuelAdapters/BurnFuelAdapter.h"
#include "Commands/ChangeVelocity/ChangeVelocity.h"
#include "Adapters/MoveAdapters/ChangeVelocityAdapter.h"
#include "Commands/Rotate/Rotate.h"
#include "Adapters/MoveAdapters/RotableAdapter.h"
#include "Exceptions/CommandException.h"
#include "MockObjects/MockObjects.h"

#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class MacroCommandTest : public ::testing::Test
    {
    public:
        MacroCommandTest() = default;
    };

    TEST_F(MacroCommandTest, simple_check_chechAndBurnFuel)
    {
        std::vector<std::unique_ptr<SpaceBattle::ICommand>> commands;
        std::any availableFuel = unsigned(10);
        std::any fuelConsumption = unsigned(3);
        std::any resultAvailableFuel = unsigned(7);
        MockUObject mockUObject;
        SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        commands.push_back(std::make_unique<SpaceBattle::CheckFuel>(checkFuelAdapter));
        commands.push_back(std::make_unique<SpaceBattle::BurnFuel>(burnFuelAdapter));
        SpaceBattle::MacroCommand macroCommand(std::move(commands));
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(2).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(2).WillRepeatedly(Return(fuelConsumption));
        EXPECT_CALL(mockUObject, setProperty("available_fuel", _)).Times(1).
            WillRepeatedly([resultAvailableFuel](std::string, std::any newAvailableFuel)
        {
            EXPECT_TRUE(std::any_cast<unsigned>(newAvailableFuel) ==
                std::any_cast<unsigned>(resultAvailableFuel));
        });
        EXPECT_NO_THROW(macroCommand.execute());
    }

    TEST_F(MacroCommandTest, exception_chechAndBurnFuel)
    {
        std::vector<std::unique_ptr<SpaceBattle::ICommand>> commands;
        std::any availableFuel = unsigned(3);
        std::any fuelConsumption = unsigned(7);
        MockUObject mockUObject;
        SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        commands.push_back(std::make_unique<SpaceBattle::CheckFuel>(checkFuelAdapter));
        commands.push_back(std::make_unique<SpaceBattle::BurnFuel>(burnFuelAdapter));
        SpaceBattle::MacroCommand macroCommand(std::move(commands));
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_THROW(macroCommand.execute(), SpaceBattle::CommandException);
    }

    TEST_F(MacroCommandTest, rotate_and_change_velocity)
    {
        std::vector<std::unique_ptr<SpaceBattle::ICommand>> commands;
        std::any angularVelocity = 45;
        std::any vectorVelocity = SpaceBattle::PositionVector{10, 10};
        std::any resultVectorVelocity = SpaceBattle::PositionVector{0, 14};
        MockUObject mockUObject;
        SpaceBattle::ChangeVelocityAdapter changeVelocityAdapter(mockUObject);
        std::any direction = SpaceBattle::Direction{15};
        std::any resultDirection = SpaceBattle::Direction{60};
        SpaceBattle::RotableAdapter rotableAdapter(mockUObject);
        commands.push_back(std::make_unique<SpaceBattle::ChangeVelocity>(changeVelocityAdapter));
        commands.push_back(std::make_unique<SpaceBattle::Rotate>(rotableAdapter));
        SpaceBattle::MacroCommand macroCommand(std::move(commands));
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(2).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("velocity", _)).Times(1).
            WillRepeatedly([resultVectorVelocity](std::string, std::any newVelocity)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newVelocity) ==
                std::any_cast<SpaceBattle::PositionVector>(resultVectorVelocity));
        });
        EXPECT_CALL(mockUObject, getProperty("direction")).Times(1).WillRepeatedly(Return(direction));
        EXPECT_CALL(mockUObject, setProperty("direction", _)).Times(1).
            WillRepeatedly([resultDirection](std::string, std::any newDirection)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::Direction>(newDirection) ==
                std::any_cast<SpaceBattle::Direction>(resultDirection));
        });
        EXPECT_NO_THROW(macroCommand.execute());
    }
}
