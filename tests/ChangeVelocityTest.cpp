#include "Commands/ChangeVelocity/ChangeVelocity.h"
#include "Adapters/MoveAdapters/ChangeVelocityAdapter.h"
#include "MockObjects/MockObjects.h"

#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class ChangeVelocityTest : public ::testing::Test
    {
    public:
        ChangeVelocityTest() = default;
    };

    TEST_F(ChangeVelocityTest, simple_rotate1)
    {
        std::any angularVelocity = 45;
        std::any vectorVelocity = SpaceBattle::PositionVector{10, 10};
        std::any resultVectorVelocity = SpaceBattle::PositionVector{0, 14};
        MockUObject mockUObject;
        SpaceBattle::ChangeVelocityAdapter changeVelocityAdapter(mockUObject);
        SpaceBattle::ChangeVelocity changeVelocity(changeVelocityAdapter);
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("velocity", _)).Times(1).
            WillRepeatedly([resultVectorVelocity](std::string, std::any newVelocity)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newVelocity) ==
                std::any_cast<SpaceBattle::PositionVector>(resultVectorVelocity));
        });
        EXPECT_NO_THROW(changeVelocity.execute());
    }

    TEST_F(ChangeVelocityTest, simple_rotate2)
    {
        std::any angularVelocity = -45;
        std::any vectorVelocity = SpaceBattle::PositionVector{0, 14};
        std::any resultVectorVelocity = SpaceBattle::PositionVector{10, 10};
        MockUObject mockUObject;
        SpaceBattle::ChangeVelocityAdapter changeVelocityAdapter(mockUObject);
        SpaceBattle::ChangeVelocity changeVelocity(changeVelocityAdapter);
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("velocity", _)).Times(1).
            WillRepeatedly([resultVectorVelocity](std::string, std::any newVelocity)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newVelocity) ==
                std::any_cast<SpaceBattle::PositionVector>(resultVectorVelocity));
        });
        EXPECT_NO_THROW(changeVelocity.execute());
    }

    TEST_F(ChangeVelocityTest, error_get_angular_velocity)
    {
        std::any angularVelocity;
        std::any vectorVelocity = SpaceBattle::PositionVector{0, 14};
        std::any resultVectorVelocity = SpaceBattle::PositionVector{10, 10};
        MockUObject mockUObject;
        SpaceBattle::ChangeVelocityAdapter changeVelocityAdapter(mockUObject);
        SpaceBattle::ChangeVelocity changeVelocity(changeVelocityAdapter);
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("velocity", _)).Times(0).
            WillRepeatedly([resultVectorVelocity](std::string, std::any newVelocity)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newVelocity) ==
                std::any_cast<SpaceBattle::PositionVector>(resultVectorVelocity));
        });
        EXPECT_THROW(changeVelocity.execute(), std::bad_any_cast);
    }

    TEST_F(ChangeVelocityTest, error_get_velocity)
    {
        std::any angularVelocity = -45;
        std::any vectorVelocity;
        std::any resultVectorVelocity = SpaceBattle::PositionVector{10, 10};
        MockUObject mockUObject;
        SpaceBattle::ChangeVelocityAdapter changeVelocityAdapter(mockUObject);
        SpaceBattle::ChangeVelocity changeVelocity(changeVelocityAdapter);
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(0).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("velocity", _)).Times(0).
            WillRepeatedly([resultVectorVelocity](std::string, std::any newVelocity)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newVelocity) ==
                std::any_cast<SpaceBattle::PositionVector>(resultVectorVelocity));
        });
        EXPECT_THROW(changeVelocity.execute(), std::bad_any_cast);
    }

    TEST_F(ChangeVelocityTest, error_set_velocity)
    {
        std::any angularVelocity = -45;
        std::any vectorVelocity = SpaceBattle::PositionVector{0, 14};
        std::any resultVectorVelocity = SpaceBattle::PositionVector{10, 10};
        MockUObject mockUObject;
        SpaceBattle::ChangeVelocityAdapter changeVelocityAdapter(mockUObject);
        SpaceBattle::ChangeVelocity changeVelocity(changeVelocityAdapter);
        EXPECT_CALL(mockUObject, getProperty("angular_velocity")).Times(1).WillRepeatedly(Return(angularVelocity));
        EXPECT_CALL(mockUObject, getProperty("velocity")).Times(1).WillRepeatedly(Return(vectorVelocity));
        EXPECT_CALL(mockUObject, setProperty("velocity", _)).Times(1).
            WillRepeatedly([resultVectorVelocity](std::string, std::any newVelocity)
        {
            EXPECT_TRUE(std::any_cast<SpaceBattle::PositionVector>(newVelocity) ==
                std::any_cast<SpaceBattle::PositionVector>(resultVectorVelocity));
            throw std::invalid_argument("");
        });
        EXPECT_THROW(changeVelocity.execute(), std::invalid_argument);
    }
}
