#include "Commands/MacroCommand/MacroCommand.h"
#include "Commands/CheckFuel/CheckFuel.h"
#include "Adapters/FuelAdapters/CheckFuelAdapter.h"
#include "Commands/BurnFuel/BurnFuel.h"
#include "Adapters/FuelAdapters/BurnFuelAdapter.h"
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

    // TEST_F(MacroCommandTest, not_enought_fuel)
    // {
    //     std::any availableFuel = unsigned(5);
    //     std::any fuelConsumption = unsigned(10);
    //     MockUObject mockUObject;
    //     SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
    //     SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
    //     EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
    //     EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
    //     EXPECT_THROW(checkFuel.execute(), SpaceBattle::FuelException);
    // }

    // TEST_F(MacroCommandTest, error_get_available_fuel)
    // {
    //     std::any availableFuel;
    //     std::any fuelConsumption = unsigned(5);
    //     MockUObject mockUObject;
    //     SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
    //     SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
    //     EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
    //     EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(0);
    //     EXPECT_THROW(checkFuel.execute(), std::bad_any_cast);
    // }

    // TEST_F(MacroCommandTest, error_get_fuel_consumption)
    // {
    //     std::any availableFuel = unsigned(10);
    //     std::any fuelConsumption;
    //     MockUObject mockUObject;
    //     SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
    //     SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
    //     EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
    //     EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
    //     EXPECT_THROW(checkFuel.execute(), std::bad_any_cast);
    // }
}
