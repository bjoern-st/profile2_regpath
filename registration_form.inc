<?php
// $Id: autoassignrole-path.inc,v 1.1.2.3 2009/09/21 19:21:18 cyberswat Exp $

/**
 * @file
 *
 * The autoassignrole-admin.inc file
 *
 * Contains path specific functionality
 */


function profile2_regpath_user_register($pid) {
  require_once drupal_get_path('module', 'user') .'/user.pages.inc';
  $output = drupal_get_form('user_register_form');
  
  return $output;
}

function _profile2_regpath_user_password() {
  require_once drupal_get_path('module', 'user') .'/user.pages.inc';
  $output = drupal_get_form('user_pass');
  return $output;
}

function _profile2_regpath_user_login() {
  require_once drupal_get_path('module', 'user') .'/user.pages.inc';
  $output = user_page();
  return $output;
}