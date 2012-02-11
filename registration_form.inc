<?php

/**
 * @file
 * Builds profile-specific register, login, and password forms.
 */

/**
 * Page callback: Displays a user login form.
 *
 * Path: [path-setting]/login
 *
 * @param object $profile2_regpath_get_profiles
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @see profile2_regpath_menu()
 */
function _profile2_regpath_user_login($profile) {
  module_load_include('pages.inc', 'user', 'user');
  $output = user_page();
  _profile2_regpath_set_title($profile, 'login_title');
  return $output;
}

/**
 * Page callback: Displays a user registration form.
 *
 * Path: [path-setting]/register
 *
 * @param object object $profile
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @see profile2_regpath_menu()
 */
function _profile2_regpath_user_register($profile) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');
  _profile2_regpath_set_title($profile, 'register_title');
  return $output;
}

/**
 * Page callback: Displays the forgot password form.
 *
 * Path: [path-setting]/password
 *
 * @param object $profile
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @see profile2_regpath_menu()
 */
function _profile2_regpath_user_password($profile) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_pass');
  _profile2_regpath_set_title($profile, 'password_title');
  return $output;
}

/**
 * Sets page title for registration, login, and forgot password pages.
 *
 * @param object $profile
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @param string $key
 *   Array key for 'misc' array. This will determine the title settings.
 */
function _profile2_regpath_set_title($profile, $key) {
  // Look for custom title.
  if (isset($profile->misc) && $misc = unserialize($profile->misc)) {
    if (array_key_exists($key, $misc)) {
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