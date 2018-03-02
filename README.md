NAME
--------------------------------
Profile2 Registration Path (profile2_regpath)


DESCRIPTION
--------------------------------
This module enables administrators to set unique registration paths per Profile2 profile type.

INSTALLATION
------------

 * Install this module using the official Backdrop CMS instructions at
   https://backdropcms.org/guide/modules

INSTRUCTIONS
--------------------------------
* Enable the module
* Go to admin/structure/profiles and edit a profile type
* Check 'Enable unique registration path'
* Enter a URL path to use for this profile type
* Save
* Logout and visit: [your-site-url]/[your-url]/register

KNOWN ISSUES
------------
When using this module the profile setting "Show during user account registration." combined 
with "Check user roles that should have this profile." doesnt work right now, but only 
the fields for that profile with this registration path are used.
So no combination of several profiles during registration is supported.


MAINTAINERS
-----------

Current maintainer:
 * Bjoern - https://github.com/bjoern-st

Current drupal maintainers:
  * Matthew Grasmick (madmatter23 on drupal.org)

CREDITS
--------------------------------
* Authored and maintained by Matthew Grasmick (madmatter23 on drupal.org)
