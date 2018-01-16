// Copyright (C) 2012-2018 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/threads/thread_data.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <cstring>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
void test_small_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr());

    // verify that sufficient stack has been allocated
    HPX_TEST(hpx::threads::get_ctx_ptr()->get_stacksize() >=
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_small));

    // allocate HPX_SMALL_STACK_SIZE - HPX_THREADS_STACK_OVERHEAD memory on
    // the stack
    char array[HPX_SMALL_STACK_SIZE-HPX_THREADS_STACK_OVERHEAD];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_DECLARE_ACTION(test_small_stacksize, test_small_stacksize_action)
HPX_ACTION_USES_SMALL_STACK(test_small_stacksize_action)
HPX_PLAIN_ACTION(test_small_stacksize, test_small_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
void test_medium_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr());

    // verify that sufficient stack has been allocated
    HPX_TEST(hpx::threads::get_ctx_ptr()->get_stacksize() >=
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_medium));

    // allocate HPX_MEDIUM_STACK_SIZE - HPX_THREADS_STACK_OVERHEAD memory on
    // the stack
    char array[HPX_MEDIUM_STACK_SIZE-HPX_THREADS_STACK_OVERHEAD];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_DECLARE_ACTION(test_medium_stacksize, test_medium_stacksize_action)
HPX_ACTION_USES_MEDIUM_STACK(test_medium_stacksize_action)
HPX_PLAIN_ACTION(test_medium_stacksize, test_medium_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
void test_large_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr());

    // verify that sufficient stack has been allocated
    HPX_TEST(hpx::threads::get_ctx_ptr()->get_stacksize() >=
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_large));

    // allocate HPX_LARGE_STACK_SIZE - HPX_THREADS_STACK_OVERHEAD memory on
    // the stack
    char array[HPX_LARGE_STACK_SIZE-HPX_THREADS_STACK_OVERHEAD];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_DECLARE_ACTION(test_large_stacksize, test_large_stacksize_action)
HPX_ACTION_USES_LARGE_STACK(test_large_stacksize_action)
HPX_PLAIN_ACTION(test_large_stacksize, test_large_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
void test_huge_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr());

    // verify that sufficient stack has been allocated
    HPX_TEST(hpx::threads::get_ctx_ptr()->get_stacksize() >=
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_huge));

    // allocate HPX_LARGE_STACK_SIZE - HPX_THREADS_STACK_OVERHEAD memory on
    // the stack
    char array[HPX_HUGE_STACK_SIZE-HPX_THREADS_STACK_OVERHEAD];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_DECLARE_ACTION(test_huge_stacksize, test_huge_stacksize_action)
HPX_ACTION_USES_HUGE_STACK(test_huge_stacksize_action)
HPX_PLAIN_ACTION(test_huge_stacksize, test_huge_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::vector<hpx::id_type> localities = hpx::find_all_localities();

    for (hpx::id_type const& id : localities)
    {
        if (id != hpx::find_here())
        {
            test_small_stacksize_action test_action;
            test_action(id);
        }

        {
            test_medium_stacksize_action test_action;
            test_action(id);
        }

        {
            test_large_stacksize_action test_action;
            test_action(id);
        }

        {
            test_huge_stacksize_action test_action;
            test_action(id);
        }
    }

    return hpx::util::report_errors();
}

