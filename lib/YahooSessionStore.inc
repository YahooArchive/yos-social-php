<?php
//
//  YahooSessionStore.inc
//  yos_sdk_php
//
//  Created by Ryan Kennedy on 6/01/09.
//  Copyright (c) 2009 Yahoo! Inc. All rights reserved.
//  
//  The copyrights embodied in the content of this file are licensed under the BSD (revised) open source license.
//
//


/**
 * The session store interface. Developers are free to implement their 
 * own session store implementations and pass them to YahooSession::hasSession,
 * YahooSession::requireSession and YahooSession::clearSession. 
 *
 * @brief The session store interface.
 */
interface YahooSessionStore {
    /**
     * Indicates if the session store has a request token.
     *
     * @return True if a request token is present, false otherwise.
     */
    function hasRequestToken(){}

    /**
     * Indicates if the session store has an access token.
     *
     * @return True if an access token is present, false otherwise.
     */
    function hasAccessToken(){}

    /**
     * Stores the given request token in the session store.
     *
     * @param $token A PHP stdclass object containing the components of 
     *               the OAuth request token.
     * @return True on success, false otherwise.
     */
    function storeRequestToken($token){}

    /**
     * Fetches and returns the request token from the session store.
     *
     * @return The request token.
     */
    function fetchRequestToken(){}

    /**
     * Clears the request token from the session store.
     *
     * @return True on success, false otherwise.
     */
    function clearRequestToken(){}

    /**
     * Stores the given access token in the session store.
     *
     * @param $token A PHP stdclass object containing the components of 
     *               the OAuth access token.
     * @return True on success, false otherwise.
     */
    function storeAccessToken($token){}

    /**
     * Fetches and returns the access token from the session store.
     *
     * @return The access token.
     */
    function fetchAccessToken(){}

    /**
     * Clears the access token from the session store.
     *
     * @return True on success, false otherwise.
     */
    function clearAccessToken(){}
}

?>
