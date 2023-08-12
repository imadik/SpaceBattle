#include "Commands/Rotate/Rotate.h"
#include "Adapters/RotableAdapter/RotableAdapter.h"
#include "MockObjects/MockObjects.h"
#include <cmath>

#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class RotateTest : public ::testing::Test
    {
    public:
        RotateTest() = default;
    };

    TEST_F(RotateTest, simple_rotate)
    {
        std::any direction = SpaceBattle::Direction{27};
        std::any angularVelocity = 33;
        std::any resultDirection = SpaceBattle::Direction{60};
        MockUObject mockUObject;
        SpaceBattle::RotableAdapter rotableAdapter(mockUObject);
        SpaceBattle::Rotate rotate(rotableAdapter);
        EXPECT_CALL(mockUObject, getProperty("direction")).Times(1).WillRepeatedly(Return(direction));
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, setProperty("direction", _)).Times(1).
            WillRepeatedly([resultDirection](std::string, std::any newDirection)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::Direction>(newDirection) ==
                std::any_cast<SpaceBattle::Direction>(resultDirection));
        });
        EXPECT_NO_THROW(rotate.execute());
    }

    TEST_F(RotateTest, error_get_direction)
    {
        std::any direction;
        std::any angularVelocity = 33;
        std::any resultDirection = SpaceBattle::Direction{60};
        MockUObject mockUObject;
        SpaceBattle::RotableAdapter rotableAdapter(mockUObject);
        SpaceBattle::Rotate rotate(rotableAdapter);
        EXPECT_CALL(mockUObject, getProperty("direction")).Times(1).WillRepeatedly(Return(direction));
        EXPECT_THROW(rotate.execute(), std::bad_any_cast);
    }

    TEST_F(RotateTest, error_get_angular_velocity)
    {
        std::any direction = SpaceBattle::Direction{27};
        std::any angularVelocity;
        std::any resultDirection = SpaceBattle::Direction{60};
        MockUObject mockUObject;
        SpaceBattle::RotableAdapter rotableAdapter(mockUObject);
        SpaceBattle::Rotate rotate(rotableAdapter);
        EXPECT_CALL(mockUObject, getProperty("direction")).Times(1).WillRepeatedly(Return(direction));
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_THROW(rotate.execute(), std::bad_any_cast);
    }

    TEST_F(RotateTest, error_set_direction)
    {
        std::any direction = SpaceBattle::Direction{27};
        std::any angularVelocity = 33;
        std::any resultDirection = SpaceBattle::Direction{60};
        MockUObject mockUObject;
        SpaceBattle::RotableAdapter rotableAdapter(mockUObject);
        SpaceBattle::Rotate rotate(rotableAdapter);
        EXPECT_CALL(mockUObject, getProperty("direction")).Times(1).WillRepeatedly(Return(direction));
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, setProperty("direction", _)).Times(1).
            WillRepeatedly([resultDirection](std::string, std::any newDirection)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::Direction>(newDirection) ==
                std::any_cast<SpaceBattle::Direction>(resultDirection));
            throw std::invalid_argument("");
        });
        EXPECT_THROW(rotate.execute(), std::invalid_argument);
    }
}
