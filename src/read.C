void read(){
  for (int i = 0; i< 10000000; i++){
    open_shm("TE13");
    h1->Draw();
  }
  return;
}
