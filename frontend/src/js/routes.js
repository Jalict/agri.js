'use strict';

/**
 * Route configuration for the RDash module.
 */
angular.module('RDash').config(['$stateProvider', '$urlRouterProvider',
    function($stateProvider, $urlRouterProvider) {

        // For unmatched routes
        $urlRouterProvider.otherwise('/');

        // Application routes
        $stateProvider
            .state('index', {
                url: '/',
                templateUrl: 'templates/dashboard.html'
            })
            .state('pumps', {
                url: '/pumps',
                templateUrl: 'templates/pumps.html'
            })
            .state('plants', {
                url: '/plants',
                templateUrl: 'templates/plants.html'
            });
    }
]);