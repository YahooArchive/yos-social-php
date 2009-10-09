Yahoo! Social SDK - PHP
=======================

Find documentation and support on Yahoo! Developer Network: http://developer.yahoo.com

 * Yahoo! Application Platform - http://developer.yahoo.com/yap/
 * Yahoo! Social APIs - http://developer.yahoo.com/social/
 * Yahoo! Query Language - http://developer.yahoo.com/yql/

Hosted on GitHub: http://github.com/yahoo/yos-social-php/tree/master


License
=======

@copyright: Copyrights for code authored by Yahoo! Inc. is licensed under the following terms:
@license:   BSD Open Source License

Yahoo! Social SDK
Software License Agreement (BSD License)
Copyright (c) 2009, Yahoo! Inc.
All rights reserved.

Redistribution and use of this software in source and binary forms, with
or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of Yahoo! Inc. nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of Yahoo! Inc.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


The Yahoo! Social PHP SDK code is subject to the BSD license, see the LICENSE file.


Requirements
============

The following dependencies are bundled with the Yahoo! PHP SDK, but are under
terms of a separate license. See the bundled LICENSE files for more information:

 * OAuth - http://code.google.com/p/oauth
 * JSON -  http://pear.php.net/Services_JSON


Install
=======

After downloading and unpackaging the release, copy the contents of yosdk/lib
to a directory that is accessible via the PHP require_once method. In
your PHP scripts, require the Yahoo.inc file:

    require_once("Yahoo.inc");

## Debugging with the YOS SDK

The YOS SDK provides some methods that make debugging easier. Also, since the YOS
SDK was designed for the greatest compatibility across PHP version, it is advised
to suppress notices if using PHP 5.x:

    // debug settings
    error_reporting(E_ALL | E_NOTICE); # do not show notices as library is php4 compatable
    ini_set('display_errors', true);

    YahooLogger::setDebug(true);
    YahooLogger::setDebugDestination('LOG');

By default, OAuth credentials (request + access tokens) are stored in PHP sessions.
PHP sessions can easily be configured to work from a local filesystem, a database, or
a memcache instance. The sample apps provide working examples of filesystem storage
and memcache storage.

## Filesystem Session Storage (default)

    // use local filesystem to store oauth credentials via php native sessions
    ini_set('session.save_handler', 'files');
    session_save_path('/tmp/');
    session_start();

## Memcache Session Storage

    // use memcache to store oauth credentials via php native sessions
    ini_set('session.save_handler', 'memcache');
    session_save_path('tcp://localhost:11211?persistent=1&weight=1&timeout=1&retry_interval=15');
    session_start();

## Cookie Based Session Storage (original)

The original default storage backend was based on storing access tokens in a plain text cookie. This is bad for security, and the default has since been changed (breaks backwards compatibility). In order to use the original
session store, you must instantiate 'CookieSessionStore' and pass into all methods of YahooSession:

    $sessionStore = new CookieSessionStore();

    YahooSession::hasSession($consumerKey, $consumerSecret, $applicationId, $sessionStore, $verifier)
    YahooSession::requireSession($consumerKey, $consumerSecret, $applicationId, $callback, $sessionStore, $verifier)
    YahooSession::initSession($consumerKey, $consumerSecret, $applicationId, $redirect, $callback, $sessionStore, $verifier)

    YahooSession::createAuthorizationUrl($consumerKey, $consumerSecret, $callback, $sessionStore)
    YahooSession::redirectForAuthorization($consumerKey, $consumerSecret, $callback, $sessionStore)
    YahooSession::clearSession($sessionStore)
    YahooSession::checkSession($sessionType, $sessionStore)


Examples
========

In the yosdk/sample directory you'll find sampleapp.php, a sample application
that will get you started. Put the file in your hosting directory and fill
in the consumer key, consumer key secret and application ID. When you're done,
point your browser at the URL. You will be directed to verify access to the
application and then you will be redirected back to your application.

In the yosdk/sample directory you'll find delicious.php, a sample yahoo open
application that shows how to use YQL to make web service request.

Make sure to update the OAuth credentials in each bundled example:

    define('OAUTH_CONSUMER_KEY', '###');
    define('OAUTH_CONSUMER_SECRET', '###');
    define('OAUTH_DOMAIN', '###');
    define('OAUTH_APP_ID', '###');


## Fetching YQL:

    $session = YahooSession::requireSession(OAUTH_CONSUMER_KEY, OAUTH_CONSUMER_SECRET, OAUTH_APP_ID);
    $user = $session->getSessionedUser();

    var_dump($session->query('select * from social.connections where owner_guid=me'));


## Fetching Social Data:

    $session = YahooSession::requireSession(OAUTH_CONSUMER_KEY, OAUTH_CONSUMER_SECRET, OAUTH_APP_ID);
    $user = $session->getSessionedUser();

    var_dump($user->getProfile());
    var_dump($user->getContacts());


## Setting YAP Small View:

    $session = YahooSession::requireSession(OAUTH_CONSUMER_KEY, OAUTH_CONSUMER_SECRET, OAUTH_APP_ID);
    $user = $session->getSessionedUser();

    $content = '<h1><yml:name> customized small view</h1>';
    var_dump($user->setSmallView($content));


## Adding a Contact:
   
    $contact_fields[] = array('type' => 'email', 'value' => 'me@domain.com');
    $contact_fields[] = array('type' => 'name', 'value' => array('givenName'=> 'John', 'familyName' => 'Doe'));
    $contact = array('fields' => $contact_fields);

    var_dump($user->addContact($contact));

Tests
=====

The Yahoo! PHP SDK comes with a test suite to validate functionality. The tests also
show functional examples and results. To run the test suite, simply execute the test suite:

    php phpunit test/OAuthTest.php
