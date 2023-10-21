#include "service-details-section.h"
#include "gtkmm/builder.h"
#include "gtkmm/enums.h"
#include "gtkmm/frame.h"

using namespace application::ui::component;

void ServiceDetailsSection::setup_components() {
    append(m_serviceproperty_title);
    append(m_serviceproperty_description);

    m_property_list_frame.set_child(m_property_listbox);
    append(m_property_list_frame);

    m_property_listbox.append(m_serviceproperty_loaded);
    m_property_listbox.append(m_serviceproperty_state);
    m_property_listbox.append(m_serviceproperty_followed);
    m_property_listbox.append(m_serviceproperty_object_path);
    m_property_listbox.append(m_serviceproperty_job_type);
    m_property_listbox.append(m_serviceproperty_job_object_path);
}

void ServiceDetailsSection::setup_style() {
    set_orientation(Gtk::Orientation::VERTICAL);

    m_serviceproperty_title.set_size_request(-1, 50);

    m_serviceproperty_description.set_max_width_chars(5);
    m_serviceproperty_description.set_wrap(true);
    m_serviceproperty_description.add_css_class("heading");
    m_serviceproperty_description.set_hexpand(false);
    m_serviceproperty_description.set_margin(10);
    m_serviceproperty_description.set_margin_top(15);
    m_serviceproperty_description.set_margin_bottom(15);

    m_property_listbox.add_css_class("rich-list");
    m_property_listbox.add_css_class("separators");
    m_property_listbox.set_selection_mode(Gtk::SelectionMode::NONE);

    m_property_list_frame.set_margin(10);
}

void ServiceDetailsSection::configure() {
    setup_components();
    setup_style();
}

ServiceDetailsSection::ServiceDetailsSection() {
    configure();
}

void ServiceDetailsSection::set_service(provider::systemd::Unit service_unit) {
    m_serviceproperty_title.set_title(service_unit.name);
    m_serviceproperty_description.set_text(service_unit.description);
    m_serviceproperty_loaded.set_value(service_unit.load_state);
    m_serviceproperty_state.set_value(service_unit.active_state + " / " + service_unit.sub_state);
    m_serviceproperty_followed.set_value(service_unit.follows);
    m_serviceproperty_object_path.set_value(service_unit.object_path);
    
    if(!service_unit.has_running_job()) {
        m_serviceproperty_job_type.set_visible(false);
        m_serviceproperty_job_object_path.set_visible(false);
    } else {
        m_serviceproperty_job_type.set_visible(true);
        m_serviceproperty_job_object_path.set_visible(true);
        m_serviceproperty_job_type.set_value(service_unit.get_running_job()->name);
        m_serviceproperty_job_object_path.set_value(service_unit.get_running_job()->path);
    }
}