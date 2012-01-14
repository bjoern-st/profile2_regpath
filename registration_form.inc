<?php

/**
 * @file
 * Builds profile-specific register, login, and password forms.
 */
function _profile2_regpath_user_register($pids = array()) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');

  /* I'd really like to do the profile attaching here, rather than in hook_form_alter(), 
   * but I don't know how I would access $form and $form_state from here.
   */

  /*
  // Get profile type(s) matching pid(s).
  $query = db_select('profile2_regpath', 'pr');
  $query->join('profile_type', 'pt', 'pr.profile_id = pt.id');
  $query->fields('pt', array('type'));
  $query->condition('pr.status', 1);
  $query->condition('pr.profile_id', $pids);
  $result = $query->execute();
  $type_names = $result->fetchAll();
  if ($type_names != NULL) {
    // Attach profile(s) to user/register form.
    foreach ($type_names as $key => $value) {
      // Get profile object.
      $type_name = (string) $type_names[$key]->type;
      $get_profile = profile2_get_types($type_name);
      // Add profile object to $form_state.
      if (empty($form_state['profiles'][$type_name])) {
        $form_state['profiles'][$type_name] = profile_create(array('type' => $type_name));
      }

      // Trigger Profile2 to attach fields from profile defined in $form_state.
      profile2_attach_form($form, $form_state);
    }
  }
  */

  return $output;
}

function _profile2_regpath_user_password() {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_pass');
  return $output;
}

function _profile2_regpath_user_login() {
  module_load_include('pages.inc', 'user', 'user');
  $output = user_page();
  return $output;
}