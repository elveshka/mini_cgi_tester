#! /usr/bin/perl
$size_of_form_information = $ENV{'CONTENT_LENGTH'};
read (STDIN, $form_info, $size_of_form_information);
($field_name, $command) = split (/=/, $form_info);
# ($lvl, $num)= split (/=/, $ARGV[0]);
print('/lvls/lvl' + $command);
