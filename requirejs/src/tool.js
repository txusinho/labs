(function(){
  var dependencies = ['user'];
  
  define (dependencies, function(app){
    return {
      start : function(user){
        user.me();
      }
    }
  })
}();
  