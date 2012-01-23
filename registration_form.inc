<?php

/**
 * @file
 * Builds profile-specific register, login, and password forms.
 */
function _profile2_regpath_user_login($profile = array()) {
  module_load_include('pages.inc', 'user', 'user');
  $output = user_page();
  _profile2_regpath_set_title($profile->misc, 'login_title');
  return $output;
}

function _profile2_regpath_user_register($profile = array()) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');
  _profile2_regpath_set_title($profile->misc, 'register_title');
  return $output;
}

function _profile2_regpath_user_password($profile = array()) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_pass');
  _profile2_regpath_set_title($profile->misc, 'password_title');
  return $output;
}

function _profile2_regpath_set_title($misc_serialized, $key) {
  // Look for custom title.
  if ($misc = unserialize($misc_serialized)) {
    if ($misc[$key]) {
      $title = $misc[$key];
    }
  }
  // Set default title.
  else {
    $title = 'User account';
  }
  // Set title.
  drupal_set_title(check_plain($title));
}