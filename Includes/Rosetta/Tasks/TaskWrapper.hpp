// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_WRAPPER_HPP
#define ROSETTASTONE_TASK_WRAPPER_HPP

#include <Rosetta/Tasks/ITask.hpp>

#include <functional>

namespace RosettaStone
{
//!
//! \brief DoBothPlayer class.
//!
//! This class represents the task that applies to both players.
//!
class DoBothPlayer : public ITask
{
 public:
    //! Constructs task with given \p task.
    //! \param task The task that applies to both players.
    explicit DoBothPlayer(ITask&& task);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    ITask& m_task;
};

//!
//! \brief DoUntil class.
//!
//! This class represents the task that is infinite-loop until completes.
//!
class DoUntil : public ITask
{
 public:
    //! Constructs task with given \p task and \p condition.
    //! \param task The task that is infinite-loop until completes.
    //! \param condition The condition under which the task completes.
    DoUntil(ITask&& task, std::function<bool(TaskStatus)>&& condition);

    //! Constructs task with given \p task and \p id.
    //! \param task The task that is infinite-loop until completes.
    //! \param id The condition whether returned TaskMeta::status is equal to
    //! id.
    DoUntil(ITask&& task, TaskStatus id);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    ITask& m_task;
    std::function<bool(TaskStatus)> m_condition;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_WRAPPER_HPP
