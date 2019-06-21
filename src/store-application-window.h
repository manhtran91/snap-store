/*
 * Copyright (C) 2019 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <gtk/gtk.h>

#include "store-application.h"

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE (StoreApplicationWindow, store_application_window, STORE, APPLICATION_WINDOW, GtkApplicationWindow)

StoreApplicationWindow *store_application_window_new (StoreApplication *application);

G_END_DECLS
