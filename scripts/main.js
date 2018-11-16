function toggle(id){
   var hiddenPost = document.getElementById(id);
   if(hiddenPost.style.display === 'none'){
       hiddenPost.style.display = 'block';
   }
   else{
       hiddenPost.style.display = 'none';
   }
}