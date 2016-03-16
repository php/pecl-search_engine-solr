The PECL compatibility library is a set of C include files whose objective is to minimize the pain of making a PHP extension compatible with PHP 5 and 7.

Project home : [https://github.com/flaupretre/pecl-pcs](https://github.com/flaupretre/pecl-pcs)

# Main features

- A set of miscellaneous compatibility macros

- A zend_string library for PHP 5

- An adaptation of most new zend_hash features for PHP 5

# Examples

For examples of using this library, look at the [PCS extension](https://github.com/flaupretre/pecl-pcs). There, you will see usage examples of almost every available features.

# Usage

Using the library is simple. Download the latest release from the [github repository](https://github.com/flaupretre/pecl-compat/releases) and insert it in your code tree. Then, include the 'compat.h' file in every '.c' source file.

# History

I first tried to port the [PHK](http://pecl.php.net/package/phk) extension to PHP 7 with a set of '#ifdef' directives. Unfortunately, it quickly became clear that it was not possible without making the code totally unreadable. Of course, for pure 'bridge' extensions, it is possible. But, as soon as you make an extensive use of hash tables and strings, it becomes impossible to maintain.

Then, I explored other solutions : separate branches duplicate code trees... without finding one I would be satisfied with, mostly because all of these bring maintainability issues : in short, separate branches bring a huge versioning problem, and separate code trees are a maintenance headache in the long term. Of course, all of this is not so serious if maintenance of PHP 5 modules stops in a couple of months, which some may hope, but my opinion is that we'll have to maintain PHP 5 versions of PHP extensions during years.

So, I reverted to the solution of keeping a single source tree and move as much conditional code as possible to a reusable compatibility layer. In order to benefit of the PHP 7 performance increase, most pecl-compat features are PHP 7 features backported to PHP 5. PHP 7 generally calls the underlying PHP functions directly, with the same performance as a pure-PHP7 development. So, when adapting your extension to use pecl-compat, you will, at the same time, change your code to use new PHP 7 features and make it compatible with both PHP 5 & 7. As a side effect, this makes it easier to discard PHP 5 compatibility in the future, when time has come.

# Supported PHP versions

5.3 and above.

