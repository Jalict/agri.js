App.controller('HomeCtrl',['$scope, $log, $http', HomeCtrl]);

function HomeCtrl($scope, $log ,$http) {

	$log.debug("did lopad homectrl");

  	$http.get('/data/dummy_data.json')
       .then(function(res){
          $scope.todos = res.data;  
          $log.debug(res);             
        });


   	$scope.alerts = [{
        type: 'success',
        msg: 'Monitoring plants are awesome!'
    }];

    $scope.addAlert = function() {
        $scope.alerts.push({
            msg: 'Another alert!'
        });
    };

    $scope.closeAlert = function(index) {
        $scope.alerts.splice(index, 1);
    };
}

