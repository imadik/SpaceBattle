#include "Commands/CheckFuel/CheckFuel.h"
#include "Adapters/FuelAdapters/CheckFuelAdapter.h"
#include "Exceptions/FuelException.h"
#include "MockObjects/MockObjects.h"

#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class CheckFuelTest : public ::testing::Test
    {
    public:
        CheckFuelTest() = default;
    };

    TEST_F(CheckFuelTest, simple_check)
    {
        std::any availableFuel = unsigned(10);
        std::any fuelConsumption = unsigned(5);
        MockUObject mockUObject;
        SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
        SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_NO_THROW(checkFuel.execute());
    }

    TEST_F(CheckFuelTest, not_enought_fuel)
    {
        std::any availableFuel = unsigned(5);
        std::any fuelConsumption = unsigned(10);
        MockUObject mockUObject;
        SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
        SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_THROW(checkFuel.execute(), SpaceBattle::FuelException);
    }

    TEST_F(CheckFuelTest, error_get_available_fuel)
    {
        std::any availableFuel;
        std::any fuelConsumption = unsigned(5);
        MockUObject mockUObject;
        SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
        SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(0);
        EXPECT_THROW(checkFuel.execute(), std::bad_any_cast);
    }

    TEST_F(CheckFuelTest, error_get_fuel_consumption)
    {
        std::any availableFuel = unsigned(10);
        std::any fuelConsumption;
        MockUObject mockUObject;
        SpaceBattle::CheckFuelAdapter checkFuelAdapter(mockUObject);
        SpaceBattle::CheckFuel checkFuel(checkFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_THROW(checkFuel.execute(), std::bad_any_cast);
    }
}
