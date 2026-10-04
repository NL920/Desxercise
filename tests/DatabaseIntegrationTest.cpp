#include <gtest/gtest.h>
#include <cstdio>

#include "Database.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "Training.hpp"
#include "Status.hpp"

TEST(DatabaseIntegrationTest, AddAndChangeTrainingInObject){
    std::remove("test.db");

    Time firststart = Time(10,41,0);
    Time firstend = Time(11,52,0);
    Date firstdate = Date(24,9,2026);
    std::string firstname = "Basen";
    Status firststatus = Status(Status::Missed);
    Training firsttr = Training(firstdate, firststart, firstend, firstname, firststatus);

    openDatabase("test.db");
    createTrainingsTable("test.db");
    addTrainingToDatabase("test.db",firsttr);

    EXPECT_EQ(firsttr.getStatus(), "Missed");

    changeTrainingStatus("test.db",firsttr, Status::Completed);

    EXPECT_EQ(firsttr.getStatus(), "Completed");

}
TEST(DatabaseIntegrationTest, AddAndChangeTrainingInDatabase){
    std::remove("test.db");

    Time firststart = Time(12,41,0);
    Time firstend = Time(13,52,0);
    Date firstdate = Date(24,9,2026);
    std::string firstname = "Basen";
    Status firststatus = Status(Status::Missed);
    Training firsttr = Training(firstdate, firststart, firstend, firstname, firststatus);

    openDatabase("test.db");
    createTrainingsTable("test.db");
    addTrainingToDatabase("test.db",firsttr);
    auto trainings = getTrainingFromDatabase("test.db","2026-09-24", "12:41:00");

    EXPECT_EQ(trainings.getName(), "Basen");
    EXPECT_EQ(trainings.getStatus(), "Missed");

}

TEST(DatabaseIntegrationTest, ChangeStatusOfNonExistingTraining){
    std::remove("test.db");

    Training training(
        Date(24, 9, 2026),
        Time(16, 41, 0),
        Time(11, 52, 0),
        "Nieistniejacy",
        Status(Status::Missed)
    );

    openDatabase("test.db");
    createTrainingsTable("test.db");

    EXPECT_THROW(changeTrainingStatus("test.db", training, Status::Completed), std::runtime_error);
        
}
