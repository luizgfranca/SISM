/*
 *   SISM - Services manager for GNU/Linux based operating systems
 *   Copyright (C) 2023 Luiz Gustavo <luizgfc@proton.me>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as
 *   published by the Free Software Foundation, either version 3 of the
 *   License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>
#include "unit.h"
#include "../dbus/systemd/systemd-manager.h"

namespace provider::systemd {
    class SystemdProvider {
        std::unique_ptr<dbus::systemd::SystemdManager> m_dbus_systemd_manager_interface;
        std::shared_ptr<std::vector<std::string>> m_unit_paths;
    public:
        // TODO use dependency injection for Systemd interfaces
        SystemdProvider();

        std::shared_ptr<std::vector<Unit>> list_loaded_or_once_loaded_units();
        std::shared_ptr<std::vector<Unit>> list_all_units();
        void start_unit(const Unit& unit);
        void stop_unit(const Unit& unit);
        void reload_or_restart_unit(const Unit& unit);
        bool enable_unit(const Unit& unit);
        bool disable_unit(const Unit& unit);
    };
}

