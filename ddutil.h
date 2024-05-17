





#ifdef _cplusplus
extern "C" {
#endif

extern void DDSetDebug (BOOL bDebug);
extern IDirectDrawSurface * DDConnectBitmap(IDirectDraw *pdd, HBITMAP hbm);
extern IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap);
extern IDirectDrawSurface * DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy);
extern HRESULT              DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
extern HRESULT              DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD                DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey2(IDirectDrawSurface *pdds, COLORREF rgb1, COLORREF rgb2);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
