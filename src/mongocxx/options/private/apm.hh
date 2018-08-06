// Copyright 2018-present MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <mongocxx/options/apm.hpp>
#include <mongocxx/private/libmongoc.hh>

#include <mongocxx/config/private/prelude.hh>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN
namespace options {

class apm_wrapper {

  using unique_callbacks = std::unique_ptr<mongoc_apm_callbacks_t, decltype(libmongoc::apm_callbacks_destroy)>;

   public:
    static void command_started(const mongoc_apm_command_started_t* event) {
        mongocxx::events::command_started_event _event(static_cast<const void*>(event));
        auto context = static_cast<apm*>(libmongoc::apm_command_started_get_context(event));
        context->command_started()(_event);
    }

    static void command_failed(const mongoc_apm_command_failed_t* event) {
        mongocxx::events::command_failed_event _event(static_cast<const void*>(event));
        auto context = static_cast<apm*>(libmongoc::apm_command_failed_get_context(event));
        context->command_failed()(_event);
    }

    static void command_succeeded(const mongoc_apm_command_succeeded_t* event) {
        mongocxx::events::command_succeeded_event _event(static_cast<const void*>(event));
        auto context = static_cast<apm*>(libmongoc::apm_command_succeeded_get_context(event));
        context->command_succeeded()(_event);
    }

    static unique_callbacks make_apm_callbacks(const apm& apm_opts) {
        mongoc_apm_callbacks_t* callbacks = libmongoc::apm_callbacks_new();

        if (apm_opts.command_started()) {
            libmongoc::apm_set_command_started_cb(callbacks, command_started);
        }

        if (apm_opts.command_failed()) {
            libmongoc::apm_set_command_failed_cb(callbacks, command_failed);
        }

        if (apm_opts.command_succeeded()) {
            libmongoc::apm_set_command_succeeded_cb(callbacks, command_succeeded);
        }

        return {callbacks, libmongoc::apm_callbacks_destroy};
    }
};

}  // namespace options
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/private/postlude.hh>
