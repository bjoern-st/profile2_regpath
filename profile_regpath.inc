<?php

/**
 * @file
 * Contains logic for modifying user registration forms.
 */

/*
 * Attach profile fields to form.
 */
function profile_regpath_attach_profile_fields(&$form, &$form_state, $form_id, $profile_types = NULL) {

  // Check to see if the form is being rebuilt after an AJAX request.
  // If so, we lost the $profile_types parameter, and need to reacquire it.
  $menu_item = menu_get_item();
  if (!$profile_types && ($menu_item['path'] == 'system/ajax' || $menu_item['path'] == 'file/ajax')) {
    $url = drupal_parse_url($form['#action']);
    $path = explode('/', str_replace('/register', '', $url['path']));
    $path_key = end($path);
    $profile_types = profile2_regpath_regpath_load_multiple(array('path' => $path_key));
  }

  if ($profile_types != NULL) {

    // Prepare variables for roles.
    $user_roles = user_roles(TRUE);

    // Attach profile(s) to user/register form.
    foreach ($profile_types as $key => $value) {
      // Get profile object.
      $type_name = (string) $profile_types[$key]->profile_type;
      $profile_type = profile2_get_types($type_name);

      // If this profile has not already been attached.
      if (empty($form_state['profiles'][$type_name])) {
        $profile = profile_create(array('type' => $type_name));
        $form_state['profiles'][$type_name] = $profile;

        $misc = unserialize($profile_types[$key]->misc);
        if ($misc['fieldset_wrap']) {
          // Wrap each profile form in a fieldset.
          $form['profile_' . $type_name] = array(
            '#type' => 'fieldset',
            '#title' => check_plain(profile2_regpath_get_profile_label($profile_types[$key]->profile_type)),
          );
        }
        // Set Form API #weight attribute for profile.
        $form['profile_' . $type_name]['#weight'] = $profile_type->weight;

        // Attach custom confirmation message to form for later display.
        if (!empty($misc['confirmation_display'])) {
          $_SESSION['profile2_regpath']['confirmation_message'] = filter_xss($misc['confirmation_message']);
        }
      }

      // Add appropriate user roles.
      $profile_roles = unserialize($value->roles);
      foreach ($profile_roles as $rid => $role_name) {
        // Add role to roles array if it isn't already there.
        if (!empty($role_name) && !array_key_exists($rid, $form['account']['roles']) && isset($user_roles[$rid])) {
          $form['account']['roles'][$rid] = array(
            '#type' => 'checkbox',
            '#title' => check_plain($user_roles[$rid]),
            '#default_value' => TRUE,
            '#disabled' => !user_access('administer users'),
          );
        }
      }

    }
    // Attach the profile fields via profile2.
    // @todo Add test for AJAX fields after profile2_attach_form() is called.
    profile2_attach_form($form, $form_state);
  }
}
