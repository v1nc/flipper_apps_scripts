#include "../infrared_i.h"

#include "common/infrared_scene_universal_common.h"

#include <infrared_extended_icons.h>

void infrared_scene_universal_projector_on_enter(void* context) {
    infrared_scene_universal_common_on_enter(context);

    Infrared* infrared = context;
    ButtonPanel* button_panel = infrared->button_panel;
    InfraredBruteForce* brute_force = infrared->brute_force;

    infrared_brute_force_set_db_filename(brute_force, EXT_PATH("infrared/projectors.ir"));
    //TODO Improve Projectors universal remote
    button_panel_reserve(button_panel, 3, 4);
    uint32_t i = 0;
    button_panel_add_item(
        button_panel,
        i,
        0,
        0,
        2,
        20,
        &I_Power,
        &I_Power_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "POWER");
    button_panel_add_item(
        button_panel,
        i,
        1,
        0,
        24,
        20,
        &I_Mute,
        &I_Mute_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "MUTE");
    button_panel_add_item(
        button_panel,
        i,
        2,
        0,
        46,
        20,
        &I_Source,
        &I_Source_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "SOURCE");
    button_panel_add_item(
        button_panel,
        i,
        0,
        1,
        2,
        44,
        &I_Vol_up,
        &I_Vol_up_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "VOL+");
    button_panel_add_item(
        button_panel,
        i,
        1,
        1,
        24,
        44,
        &I_Up,
        &I_Up_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "UP");
    button_panel_add_item(
        button_panel,
        i,
        2,
        1,
        46,
        44,
        &I_Vol_down,
        &I_Vol_down_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "VOL-");
    button_panel_add_item(
        button_panel,
        i,
        0,
        2,
        2,
        68,
        &I_Left,
        &I_Left_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "LEFT");
    button_panel_add_item(
        button_panel,
        i,
        1,
        2,
        24,
        68,
        &I_Ok,
        &I_Ok_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "OK");
    button_panel_add_item(
        button_panel,
        i,
        2,
        2,
        46,
        68,
        &I_Right,
        &I_Right_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "RIGHT");
    button_panel_add_item(
        button_panel,
        i,
        0,
        3,
        2,
        92,
        &I_Menu,
        &I_Menu_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "MENU");
    button_panel_add_item(
        button_panel,
        i,
        1,
        3,
        24,
        92,
        &I_Down,
        &I_Down_hvr,
        infrared_scene_universal_common_item_callback,
        context);
    infrared_brute_force_add_record(brute_force, i++, "DOWN");   
    button_panel_add_item(
        button_panel,
        i,
        2,
        3,
        46,
        92,
        &I_Empty,
        &I_Empty,
        NULL,
        context);
    infrared_brute_force_add_record(brute_force, i++, "");

    button_panel_add_label(button_panel, 10, 11, FontPrimary, "Projector");

    view_set_orientation(view_stack_get_view(infrared->view_stack), ViewOrientationVertical);
    view_dispatcher_switch_to_view(infrared->view_dispatcher, InfraredViewStack);

    infrared_show_loading_popup(infrared, true);
    bool success = infrared_brute_force_calculate_messages(brute_force);
    infrared_show_loading_popup(infrared, false);

    if(!success) {
        scene_manager_next_scene(infrared->scene_manager, InfraredSceneErrorDatabases);
    }
}

bool infrared_scene_universal_projector_on_event(void* context, SceneManagerEvent event) {
    return infrared_scene_universal_common_on_event(context, event);
}

void infrared_scene_universal_projector_on_exit(void* context) {
    infrared_scene_universal_common_on_exit(context);
}
