int getNote(int cvValue)
{
  int playingNote = 0;
  for (int i = 0; i < 60; i++)
  {
    if (isBetween(cvValue, cvNotesFromKb[i] - 4, cvNotesFromKb[i] + 4) == true)
    {
      return i;
    }
  }
  return 0;
}

bool isBetween(int val, int x, int y)
{
  if (val > x && val < y)
  {
    return true;
  }
  else
  {
    return false;
  }
}
