define(['src/main'], function(main){
       
  describe("The application should load", function() {

    var app = main;

    it("should have a me function", function() {
      expect(app.me).not.toBe(undefined);
    });


  });
});