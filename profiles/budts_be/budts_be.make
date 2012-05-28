core = 7.x
api = 2

projects[drupal][type] = "core"
projects[drupal][patch][] = "patches/gitignore.patch"
projects[drupal][patch][] = "patches/htaccess.patch"

projects[tao][type] = "theme"

projects[ctools][subdir] = "contrib"
projects[custom_breadcrumbs][subdir] = "contrib"
projects[custom_breadcrumbs][version] = "2.x-dev"
projects[features][subdir] = "contrib"
projects[feeds][subdir] = "contrib"
projects[geshifilter][subdir] = "contrib"
projects[gravatar][subdir] = "contrib"
projects[job_scheduler][subdir] = "contrib"
projects[menu_block][subdir] = "contrib"
projects[mollom][subdir] = "contrib"
projects[pathauto][subdir] = "contrib"
projects[token][subdir] = "contrib"
projects[strongarm][subdir] = "contrib"
projects[subpathauto][subdir] = "contrib"
projects[tagadelic][subdir] = "contrib"
projects[views][subdir] = "contrib"
projects[webform][subdir] = "contrib"

; todo
; 1. patch for .htaccess
; 2. patch for .gitignore
; 3. patch for tagadelic
