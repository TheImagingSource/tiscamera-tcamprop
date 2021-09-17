/*
 * Copyright 2021 The Imaging Source Europe GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TCAMPROP_1_0_H
#define TCAMPROP_1_0_H

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

typedef enum {
    TCAM_ERROR_SUCCESS                      = 0,
    TCAM_ERROR_UNKNOWN                      = 1,
    TCAM_ERROR_PROPERTY_NOT_IMPLEMENTED     = 2,
    TCAM_ERROR_PROPERTY_NOT_AVAILABLE       = 3,
    TCAM_ERROR_PROPERTY_NOT_WRITEABLE       = 4,
    TCAM_ERROR_PROPERTY_TYPE_INCOMPATIBLE   = 5,
    TCAM_ERROR_PROPERTY_VALUE_OUT_OF_RANGE  = 6,
    TCAM_ERROR_NO_DEVICE_OPEN               = 7,
    TCAM_ERROR_DEVICE_LOST                  = 8,
    TCAM_ERROR_PARAMETER_NULL               = 9,
} TcamError;

typedef enum {
    TCAM_PROPERTY_TYPE_BOOLEAN      = 0,
    TCAM_PROPERTY_TYPE_INTEGER      = 1,
    TCAM_PROPERTY_TYPE_FLOAT        = 2,
    TCAM_PROPERTY_TYPE_ENUMERATION  = 3,
    TCAM_PROPERTY_TYPE_COMMAND      = 4,
} TcamPropertyType;

typedef enum {
    TCAM_PROPERTY_VISIBILITY_BEGINNER = 0,
    TCAM_PROPERTY_VISIBILITY_EXPERT = 1,
    TCAM_PROPERTY_VISIBILITY_GURU = 2,
    TCAM_PROPERTY_VISIBILITY_INVISIBLE = 3,
} TcamPropertyVisibility;

typedef enum  {
    TCAM_PROPERTY_INTREPRESENTATION_LINEAR = 0,
    TCAM_PROPERTY_INTREPRESENTATION_LOGARITHMIC = 1,
    TCAM_PROPERTY_INTREPRESENTATION_PURENUMBER = 2,
    TCAM_PROPERTY_INTREPRESENTATION_HEXNUMBER = 3,
} TcamPropertyIntRepresentation;

typedef enum {
    TCAM_PROPERTY_FLOATREPRESENTATION_LINEAR = 0,
    TCAM_PROPERTY_FLOATREPRESENTATION_LOGARITHMIC = 1,
    TCAM_PROPERTY_FLOATREPRESENTATION_PURENUMBER = 2,
} TcamPropertyFloatRepresentation;

#define TCAM_TYPE_PROPBASE tcam_prop_base_get_type()
G_DECLARE_INTERFACE( TcamPropBase, tcam_prop_base, TCAM, PROPBASE, GObject )

struct _TcamPropBaseInterface
{
    GTypeInterface parent_interface;

    const gchar* (*get_name)(TcamPropBase* self);
    const gchar* (*get_display_name)(TcamPropBase* self);
    const gchar* (*get_description)(TcamPropBase* self);
    const gchar* (*get_category)(TcamPropBase* self);

    TcamPropertyVisibility (*get_visibility)(TcamPropBase* self);

    TcamPropertyType (*get_prop_type)(TcamPropBase* self);

    gboolean (*is_available)(TcamPropBase* self, GError** err );
    gboolean (*is_locked)(TcamPropBase* self, GError** err);
};

#define TCAM_TYPE_PROPBOOLEAN tcam_prop_boolean_get_type()
G_DECLARE_INTERFACE( TcamPropBoolean, tcam_prop_boolean, TCAM, PROPBOOLEAN, TcamPropBase )

struct _TcamPropBooleanInterface
{
    GTypeInterface parent_interface;

    gboolean    (*get_value)(TcamPropBoolean* self, GError** err);
    void        (*set_value)(TcamPropBoolean* self, gboolean value, GError** err);

    gboolean    (*get_default)(TcamPropBoolean* self, GError** err);
};


#define TCAM_TYPE_PROPINTEGER tcam_prop_integer_get_type()
G_DECLARE_INTERFACE( TcamPropInteger, tcam_prop_integer, TCAM, PROPINTEGER, TcamPropBase )

struct _TcamPropIntegerInterface
{
    GTypeInterface parent_interface;

    gint64      (*get_value)(TcamPropInteger* self, GError** err);
    void        (*set_value)(TcamPropInteger* self, gint64 value, GError** err);

    void        (*get_range)(TcamPropInteger* self, gint64* min_value, gint64* max_value, gint64* default_value, gint64* step_value, GError** err);

    const gchar* (*get_unit)(TcamPropInteger* self);
    TcamPropertyIntRepresentation   (*get_representation)(TcamPropInteger* self );
};


#define TCAM_TYPE_PROPFLOAT tcam_prop_float_get_type()
G_DECLARE_INTERFACE( TcamPropFloat, tcam_prop_float, TCAM, PROPFLOAT, TcamPropBase )

struct _TcamPropFloatInterface
{
    GTypeInterface parent_interface;

    gdouble     (*get_value)(TcamPropFloat* self, GError** err);
    void        (*set_value)(TcamPropFloat* self, gdouble value, GError** err);

    void        (*get_range)(TcamPropFloat* self, gdouble* min_value, gdouble* max_value, gdouble* default_value, gdouble* step_value, GError** err);
    const gchar* (*get_unit)(TcamPropFloat* self);
    TcamPropertyFloatRepresentation( *get_representation )(TcamPropFloat* self);
};

#define TCAM_TYPE_PROPENUMERATION tcam_prop_enumeration_get_type()
G_DECLARE_INTERFACE( TcamPropEnumeration, tcam_prop_enumeration, TCAM, PROPENUMERATION, TcamPropBase )

struct _TcamPropEnumerationInterface
{
    GTypeInterface parent_interface;

    char*       (*get_value)(TcamPropEnumeration* self, GError** err);
    void        (*set_value)(TcamPropEnumeration* self, const char* value, GError** err);

    GSList*     (*get_enum_entries)(TcamPropEnumeration* self, GError** err );
    const char* (*get_default)(TcamPropEnumeration* self, GError** err);
};

#define TCAM_TYPE_PROPCOMMAND tcam_prop_command_get_type()
G_DECLARE_INTERFACE( TcamPropCommand, tcam_prop_command, TCAM, PROPCOMMAND, TcamPropBase )

struct _TcamPropCommandInterface
{
    GTypeInterface parent_interface;

    void        (*execute_command)(TcamPropCommand* self, GError** err);
};

#define TCAM_TYPE_PROPPROVIDER tcam_prop_provider_get_type()
G_DECLARE_INTERFACE( TcamPropProvider, tcam_prop_provider, TCAM, PROPPROVIDER, GObject )

struct _TcamPropProviderInterface
{
    GTypeInterface parent_interface;

    GSList*         (*get_tcam_property_names) (TcamPropProvider* self, GError** err);
    TcamPropBase*   (*get_tcam_property)(TcamPropProvider* self, const char* name, GError** err);
};

G_END_DECLS

#endif
