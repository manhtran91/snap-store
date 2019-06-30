/*
 * Copyright (C) 2019 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "store-window.h"

#include "store-app-page.h"
#include "store-home-page.h"
#include "store-snap-pool.h"

struct _StoreWindow
{
    GtkApplicationWindow parent_instance;

    StoreAppPage *app_page;
    GtkButton *back_button;
    StoreHomePage *home_page;
    GtkStack *stack;

    StoreCache *cache;
    StoreOdrsClient *odrs_client;
};

G_DEFINE_TYPE (StoreWindow, store_window, GTK_TYPE_APPLICATION_WINDOW)

static void
app_activated_cb (StoreWindow *self, StoreApp *app)
{
    store_window_show_app (self, app);
}

static void
back_button_clicked_cb (StoreWindow *self)
{
    gtk_stack_set_visible_child (self->stack, GTK_WIDGET (self->home_page));
    gtk_widget_hide (GTK_WIDGET (self->back_button));
}

static void
store_window_dispose (GObject *object)
{
    StoreWindow *self = STORE_WINDOW (object);

    g_clear_object (&self->cache);
    g_clear_object (&self->odrs_client);

    G_OBJECT_CLASS (store_window_parent_class)->dispose (object);
}

static void
store_window_class_init (StoreWindowClass *klass)
{
    G_OBJECT_CLASS (klass)->dispose = store_window_dispose;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass), "/io/snapcraft/Store/store-window.ui");

    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (klass), StoreWindow, app_page);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (klass), StoreWindow, back_button);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (klass), StoreWindow, home_page);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (klass), StoreWindow, stack);

    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), app_activated_cb);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), back_button_clicked_cb);
}

static void
store_window_init (StoreWindow *self)
{
    store_app_page_get_type ();
    store_home_page_get_type ();
    gtk_widget_init_template (GTK_WIDGET (self));

    gtk_window_set_default_size (GTK_WINDOW (self), 800, 600); // FIXME: Temp
}

StoreWindow *
store_window_new (StoreApplication *application)
{
    return g_object_new (store_window_get_type (),
                         "application", application,
                         NULL);
}

void
store_window_set_cache (StoreWindow *self, StoreCache *cache)
{
    g_return_if_fail (STORE_IS_WINDOW (self));

    g_set_object (&self->cache, cache);

    store_app_page_set_cache (self->app_page, cache);
    store_home_page_set_cache (self->home_page, cache);
}

void
store_window_set_odrs_client (StoreWindow *self, StoreOdrsClient *odrs_client)
{
    g_return_if_fail (STORE_IS_WINDOW (self));

    g_set_object (&self->odrs_client, odrs_client);

    store_app_page_set_odrs_client (self->app_page, odrs_client);
    store_home_page_set_odrs_client (self->home_page, odrs_client);
}

void
store_window_set_snap_pool (StoreWindow *self, StoreSnapPool *pool)
{
    g_return_if_fail (STORE_IS_WINDOW (self));
    store_home_page_set_snap_pool (self->home_page, pool);
}

void
store_window_load (StoreWindow *self)
{
    g_return_if_fail (STORE_IS_WINDOW (self));

    store_home_page_load (self->home_page);
}

void
store_window_show_app (StoreWindow *self, StoreApp *app)
{
    g_return_if_fail (STORE_IS_WINDOW (self));

    store_app_page_set_app (self->app_page, app);
    gtk_stack_set_visible_child (self->stack, GTK_WIDGET (self->app_page));
    gtk_widget_show (GTK_WIDGET (self->back_button));
}
