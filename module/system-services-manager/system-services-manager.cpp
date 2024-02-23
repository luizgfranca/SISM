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


#include "system-services-manager.h"
#include <memory>

using namespace module::services;

void SystemServicesManager::start_service(const provider::systemd::Unit& service) {
    m_systemd_provider.start_unit(service);
}

void SystemServicesManager::stop_service(const provider::systemd::Unit& service) {
    m_systemd_provider.stop_unit(service);
}

void SystemServicesManager::restart_service(const provider::systemd::Unit& service) {
    m_systemd_provider.reload_or_restart_unit(service);
}

std::shared_ptr<std::vector<provider::systemd::Unit>> SystemServicesManager::get_services_list() {
    return provider::systemd::Unit::filter_by_type(
        m_systemd_provider.list_all_units(), 
        "service"
    ); 
}

// returns new service autostart setting value
bool SystemServicesManager::set_service_autostart(const provider::systemd::Unit& service, bool should_autostart) {
    return should_autostart 
        ? m_systemd_provider.enable_unit(service) 
        : !m_systemd_provider.disable_unit(service);
}