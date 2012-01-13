<?php
// $Id: autoassignrole-path.inc,v 1.1.2.3 2009/09/21 19:21:18 cyberswat Exp $

/**
 * @file
 *
 * The autoassignrole-admin.inc file
 *
 * Contains path specific functionality
 */


function _profile2_regpath_user_register($pid) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');
  
  $type_name = (string) db_query("SELECT pt.type FROM {profile_type} pt LEFT JOIN {profile2_regpath} pr ON pt.id = pr.profile_id WHERE pr.profile_id = :pid AND pr.status = 1", array(':pid' => $pid))->fetchField();  
  
  if ($type_name != NULL) {
    // Get profile object.
    $get_profile = profile2_get_types($type_name);

    // Add profile object to $form_state.
    if (empty($form_state['profiles'][$type_name])) {
      $form_state['profiles'][$type_name] = profile_create(array('type' => $type_name));
    }

    // Trigger Profile2 to attach fields from profile defined in $form_state.
    profile2_attach_form($form, $form_state);
  }

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