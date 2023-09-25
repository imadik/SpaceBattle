#include "Commands/BurnFuel/BurnFuel.h"
#include "Adapters/FuelAdapters/BurnFuelAdapter.h"
#include "Exceptions/FuelException.h"
#include "MockObjects/MockObjects.h"

#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class BurnFuelTest : public ::testing::Test
    {
    public:
        BurnFuelTest() = default;
    };

    TEST_F(BurnFuelTest, simple_move)
    {
        std::any availableFuel = unsigned(10);
        std::any fuelConsumption = unsigned(3);
        std::any resultAvailableFuel = unsigned(7);
        MockUObject mockUObject;
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        SpaceBattle::BurnFuel burnFuel(burnFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_CALL(mockUObject, setProperty("available_fuel", _)).Times(1).
            WillRepeatedly([resultAvailableFuel](std::string, std::any newAvailableFuel)
        {
            EXPECT_TRUE(std::any_cast<unsigned>(newAvailableFuel) ==
                std::any_cast<unsigned>(resultAvailableFuel));
        });
        EXPECT_NO_THROW(burnFuel.execute());
    }

    TEST_F(BurnFuelTest, not_enought_fuel)
    {
        std::any availableFuel = unsigned(5);
        std::any fuelConsumption = unsigned(10);
        MockUObject mockUObject;
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        SpaceBattle::BurnFuel burnFuel(burnFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_THROW(burnFuel.execute(), SpaceBattle::FuelException);
    }

    TEST_F(BurnFuelTest, error_get_available_fuel)
    {
        std::any availableFuel;
        std::any fuelConsumption = unsigned(5);
        MockUObject mockUObject;
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        SpaceBattle::BurnFuel burnFuel(burnFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(0);
        EXPECT_THROW(burnFuel.execute(), std::bad_any_cast);
    }

    TEST_F(BurnFuelTest, error_get_fuel_consumption)
    {
        std::any availableFuel = unsigned(10);
        std::any fuelConsumption;
        MockUObject mockUObject;
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        SpaceBattle::BurnFuel burnFuel(burnFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_THROW(burnFuel.execute(), std::bad_any_cast);
    }

    TEST_F(BurnFuelTest, error_set_position)
    {
        std::any availableFuel = unsigned(10);
        std::any fuelConsumption = unsigned(3);
        std::any resultAvailableFuel = unsigned(7);
        MockUObject mockUObject;
        SpaceBattle::BurnFuelAdapter burnFuelAdapter(mockUObject);
        SpaceBattle::BurnFuel burnFuel(burnFuelAdapter);
        EXPECT_CALL(mockUObject, getProperty("available_fuel")).Times(1).WillRepeatedly(Return(availableFuel));
        EXPECT_CALL(mockUObject, getProperty("fuel_consumption")).Times(1).WillRepeatedly(Return(fuelConsumption));
        EXPECT_CALL(mockUObject, setProperty("available_fuel", _)).Times(1).
            WillRepeatedly([resultAvailableFuel](std::string, std::any newAvailableFuel)
        {
            EXPECT_TRUE(std::any_cast<unsigned>(newAvailableFuel) ==
                std::any_cast<unsigned>(resultAvailableFuel));
            throw std::invalid_argument("");
        });
        EXPECT_THROW(burnFuel.execute(), std::invalid_argument);
    }
}
