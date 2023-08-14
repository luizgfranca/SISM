#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/Types.h>













namespace client::dbus::systemd {
    typedef     
    std::vector<
        sdbus::Struct<
            std::string, // The primary unit name as string
            std::string, // The human readable description string
            std::string, // The load state (i.e. whether the unit file has been loaded successfully)
            std::string, // The active state (i.e. whether the unit is currently started or not)
            std::string, // The sub state (a more fine-grained version of the active state that is specific to the unit type, which the active state is not)
            std::string, // A unit that is being followed in its state by this unit, if there is any, otherwise the empty string.
            sdbus::ObjectPath, // The unit object path
            uint32_t, // If there is a job queued for the job unit the numeric job id, 0 otherwise
            std::string, // The job type as string
            sdbus::ObjectPath // The job object path
        >
    > list_units_response_t;


    class SystemdManager {
        std::unique_ptr<sdbus::IProxy> proxy;
    public:
        SystemdManager();
        list_units_response_t list_units();
        void stop_unit(std::string unit_name);
    };
}