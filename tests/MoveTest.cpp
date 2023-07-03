#include "Move/Move.h"
#include "MovableAdapter/MovableAdapter.h"
#include "MockObjects/MockObjects.h"
#include <cmath>

#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class MoveTest : public ::testing::Test
    {
    public:
        MoveTest() = default;
    };

    TEST_F(MoveTest, simple_move)
    {
        std::any vectorPosition = SpaceBattle::PositionVector{12, 5};
        std::any vectorVelocity = SpaceBattle::PositionVector{-7, 3};
        std::any vectorResultPosition = SpaceBattle::PositionVector{5, 8};
        MockUObject mockUObject;
        SpaceBattle::MovableAdapter moveAdapter(mockUObject);
        SpaceBattle::Move move(moveAdapter);
        EXPECT_CALL(mockUObject, getProperty("position")).Times(1).WillRepeatedly(Return(vectorPosition));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("position", _)).Times(1).
            WillRepeatedly([vectorResultPosition](std::string, std::any newPosition)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newPosition) ==
                std::any_cast<SpaceBattle::PositionVector>(vectorResultPosition));
        });
        EXPECT_NO_THROW(move.execute());
    }

    TEST_F(MoveTest, error_get_position)
    {
        std::any vectorPosition;
        std::any vectorVelocity = SpaceBattle::PositionVector{-7, 3};
        MockUObject mockUObject;
        SpaceBattle::MovableAdapter moveAdapter(mockUObject);
        SpaceBattle::Move move(moveAdapter);
        EXPECT_CALL(mockUObject, getProperty("position")).Times(1).WillRepeatedly(Return(vectorPosition));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_THROW(move.execute(), std::bad_any_cast);
    }

    TEST_F(MoveTest, error_get_velocity)
    {
        std::any vectorVelocity;
        MockUObject mockUObject;
        SpaceBattle::MovableAdapter moveAdapter(mockUObject);
        SpaceBattle::Move move(moveAdapter);
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_THROW(move.execute(), std::bad_any_cast);
    }

    TEST_F(MoveTest, error_set_position)
    {
        std::any vectorPosition = SpaceBattle::PositionVector{12, 5};
        std::any vectorVelocity = SpaceBattle::PositionVector{-7, 3};
        std::any vectorResultPosition = SpaceBattle::PositionVector{5, 8};
        MockUObject mockUObject;
        SpaceBattle::MovableAdapter moveAdapter(mockUObject);
        SpaceBattle::Move move(moveAdapter);
        EXPECT_CALL(mockUObject, getProperty("position")).Times(1).WillRepeatedly(Return(vectorPosition));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("position", _)).Times(1).
            WillRepeatedly([vectorResultPosition](std::string, std::any newPosition)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newPosition) ==
                std::any_cast<SpaceBattle::PositionVector>(vectorResultPosition));
            throw std::invalid_argument("");
        });
        EXPECT_THROW(move.execute(), std::invalid_argument);
    }
}
