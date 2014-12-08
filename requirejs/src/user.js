define('user', function(){
  var name= 'Txus';
  var surname= 'Ordorika';
  console.log('user loaded');
  return {
    me : function(){
      console.log(name + ' '+surname);
  }};
});
    