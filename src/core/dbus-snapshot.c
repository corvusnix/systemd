/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

/***
  This file is part of systemd.

  Copyright 2010 Lennart Poettering

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include "selinux-access.h"
#include "unit.h"
#include "snapshot.h"
#include "dbus-unit.h"
#include "dbus-snapshot.h"

int bus_snapshot_method_remove(sd_bus *bus, sd_bus_message *message, void *userdata) {
        Snapshot *s = userdata;

        assert(bus);
        assert(message);
        assert(s);

        SELINUX_UNIT_ACCESS_CHECK(UNIT(s), bus, message, "stop");

        snapshot_remove(s);

        return sd_bus_reply_method_return(bus, message, NULL);
}

const sd_bus_vtable bus_snapshot_vtable[] = {
        SD_BUS_VTABLE_START(0),
        SD_BUS_METHOD("Remove", NULL, NULL, bus_snapshot_method_remove, 0),
        SD_BUS_PROPERTY("Cleanup", "b", bus_property_get_bool, offsetof(Snapshot, cleanup), 0),
        SD_BUS_VTABLE_END
};
